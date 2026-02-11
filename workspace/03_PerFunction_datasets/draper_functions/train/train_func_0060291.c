btrfs_destroy_pinned_extent(struct btrfs_root *root,
				       struct extent_io_tree *pinned_extents)
{
	struct extent_io_tree *unpin;
	u64 start;
	u64 end;
	int ret;
	bool loop = true;

	unpin = pinned_extents;
again:
	while (1) {
		ret = find_first_extent_bit(unpin, 0, &start, &end,
					    EXTENT_DIRTY, NULL);
		if (ret)
			break;

		clear_extent_dirty(unpin, start, end, GFP_NOFS);
		btrfs_error_unpin_extent_range(root, start, end);
		cond_resched();
	}

	if (loop) {
		if (unpin == &root->fs_info->freed_extents[0])
			unpin = &root->fs_info->freed_extents[1];
		else
			unpin = &root->fs_info->freed_extents[0];
		loop = false;
		goto again;
	}

	return 0;
}
