btree_readpage_end_io_hook(struct btrfs_io_bio *io_bio,
				      u64 phy_offset, struct page *page,
				      u64 start, u64 end, int mirror)
{
	u64 found_start;
	int found_level;
	struct extent_buffer *eb;
	struct btrfs_root *root = BTRFS_I(page->mapping->host)->root;
	int ret = 0;
	int reads_done;

	if (!page->private)
		goto out;

	eb = (struct extent_buffer *)page->private;


	extent_buffer_get(eb);

	reads_done = atomic_dec_and_test(&eb->io_pages);
	if (!reads_done)
		goto err;

	eb->read_mirror = mirror;
	if (test_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags)) {
		ret = -EIO;
		goto err;
	}

	found_start = btrfs_header_bytenr(eb);
	if (found_start != eb->start) {
		btrfs_err_rl(eb->fs_info, "bad tree block start %llu %llu",
			       found_start, eb->start);
		ret = -EIO;
		goto err;
	}
	if (check_tree_block_fsid(root->fs_info, eb)) {
		btrfs_err_rl(eb->fs_info, "bad fsid on block %llu",
			       eb->start);
		ret = -EIO;
		goto err;
	}
	found_level = btrfs_header_level(eb);
	if (found_level >= BTRFS_MAX_LEVEL) {
		btrfs_err(root->fs_info, "bad tree block level %d",
			   (int)btrfs_header_level(eb));
		ret = -EIO;
		goto err;
	}

	btrfs_set_buffer_lockdep_class(btrfs_header_owner(eb),
				       eb, found_level);

	ret = csum_tree_block(root->fs_info, eb, 1);
	if (ret) {
		ret = -EIO;
		goto err;
	}


	if (found_level == 0 && check_leaf(root, eb)) {
		set_bit(EXTENT_BUFFER_CORRUPT, &eb->bflags);
		ret = -EIO;
	}

	if (!ret)
		set_extent_buffer_uptodate(eb);
err:
	if (reads_done &&
	    test_and_clear_bit(EXTENT_BUFFER_READAHEAD, &eb->bflags))
		btree_readahead_hook(root, eb, eb->start, ret);

	if (ret) {


		atomic_inc(&eb->io_pages);
		clear_extent_buffer_uptodate(eb);
	}
	free_extent_buffer(eb);
out:
	return ret;
}
