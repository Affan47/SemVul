scrub_submit_raid56_bio_wait(struct btrfs_fs_info *fs_info,
					struct bio *bio,
					struct scrub_page *page)
{
	struct scrub_bio_ret done;
	int ret;

	init_completion(&done.event);
	done.error = 0;
	bio->bi_iter.bi_sector = page->logical >> 9;
	bio->bi_private = &done;
	bio->bi_end_io = scrub_bio_wait_endio;

	ret = raid56_parity_recover(fs_info->fs_root, bio, page->recover->bbio,
				    page->recover->map_length,
				    page->mirror_num, 0);
	if (ret)
		return ret;

	wait_for_completion(&done.event);
	if (done.error)
		return -EIO;

	return 0;
}
