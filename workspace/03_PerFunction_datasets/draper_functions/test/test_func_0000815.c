bio_readpage_error(struct bio *failed_bio, u64 phy_offset,
			      struct page *page, u64 start, u64 end,
			      int failed_mirror)
{
	struct io_failure_record *failrec;
	struct inode *inode = page->mapping->host;
	struct extent_io_tree *tree = &BTRFS_I(inode)->io_tree;
	struct bio *bio;
	int read_mode;
	int ret;

	BUG_ON(failed_bio->bi_rw & REQ_WRITE);

	ret = btrfs_get_io_failure_record(inode, start, end, &failrec);
	if (ret)
		return ret;

	ret = btrfs_check_repairable(inode, failed_bio, failrec, failed_mirror);
	if (!ret) {
		free_io_failure(inode, failrec);
		return -EIO;
	}

	if (failed_bio->bi_vcnt > 1)
		read_mode = READ_SYNC | REQ_FAILFAST_DEV;
	else
		read_mode = READ_SYNC;

	phy_offset >>= inode->i_sb->s_blocksize_bits;
	bio = btrfs_create_repair_bio(inode, failed_bio, failrec, page,
				      start - page_offset(page),
				      (int)phy_offset, failed_bio->bi_end_io,
				      NULL);
	if (!bio) {
		free_io_failure(inode, failrec);
		return -EIO;
	}

	pr_debug("Repair Read Error: submitting new read[%#x] to this_mirror=%d, in_validation=%d\n",
		 read_mode, failrec->this_mirror, failrec->in_validation);

	ret = tree->ops->submit_bio_hook(inode, read_mode, bio,
					 failrec->this_mirror,
					 failrec->bio_flags, 0);
	if (ret) {
		free_io_failure(inode, failrec);
		bio_put(bio);
	}

	return ret;
}
