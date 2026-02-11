btrfs_exclude_logged_extents(struct btrfs_root *log,
				 struct extent_buffer *eb)
{
	struct btrfs_file_extent_item *item;
	struct btrfs_key key;
	int found_type;
	int i;

	if (!btrfs_fs_incompat(log->fs_info, MIXED_GROUPS))
		return 0;

	for (i = 0; i < btrfs_header_nritems(eb); i++) {
		btrfs_item_key_to_cpu(eb, &key, i);
		if (key.type != BTRFS_EXTENT_DATA_KEY)
			continue;
		item = btrfs_item_ptr(eb, i, struct btrfs_file_extent_item);
		found_type = btrfs_file_extent_type(eb, item);
		if (found_type == BTRFS_FILE_EXTENT_INLINE)
			continue;
		if (btrfs_file_extent_disk_bytenr(eb, item) == 0)
			continue;
		key.objectid = btrfs_file_extent_disk_bytenr(eb, item);
		key.offset = btrfs_file_extent_disk_num_bytes(eb, item);
		__exclude_logged_extent(log, key.objectid, key.offset);
	}

	return 0;
}
