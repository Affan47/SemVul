btrfs_mark_buffer_dirty(struct extent_buffer *buf)
{
	struct btrfs_root *root;
	u64 transid = btrfs_header_generation(buf);
	int was_dirty;

#ifdef CONFIG_BTRFS_FS_RUN_SANITY_TESTS


	if (unlikely(test_bit(EXTENT_BUFFER_DUMMY, &buf->bflags)))
		return;
#endif
	root = BTRFS_I(buf->pages[0]->mapping->host)->root;
	btrfs_assert_tree_locked(buf);
	if (transid != root->fs_info->generation)
		WARN(1, KERN_CRIT "btrfs transid mismatch buffer %llu, "
		       "found %llu running %llu\n",
			buf->start, transid, root->fs_info->generation);
	was_dirty = set_extent_buffer_dirty(buf);
	if (!was_dirty)
		__percpu_counter_add(&root->fs_info->dirty_metadata_bytes,
				     buf->len,
				     root->fs_info->dirty_metadata_batch);
#ifdef CONFIG_BTRFS_FS_CHECK_INTEGRITY
	if (btrfs_header_level(buf) == 0 && check_leaf(root, buf)) {
		btrfs_print_leaf(root, buf);
		ASSERT(0);
	}
#endif
}
