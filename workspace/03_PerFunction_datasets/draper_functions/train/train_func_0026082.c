do_trimming(struct btrfs_block_group_cache *block_group,
		       u64 *total_trimmed, u64 start, u64 bytes,
		       u64 reserved_start, u64 reserved_bytes,
		       struct btrfs_trim_range *trim_entry)
{
	struct btrfs_space_info *space_info = block_group->space_info;
	struct btrfs_fs_info *fs_info = block_group->fs_info;
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	int ret;
	int update = 0;
	u64 trimmed = 0;

	spin_lock(&space_info->lock);
	spin_lock(&block_group->lock);
	if (!block_group->ro) {
		block_group->reserved += reserved_bytes;
		space_info->bytes_reserved += reserved_bytes;
		update = 1;
	}
	spin_unlock(&block_group->lock);
	spin_unlock(&space_info->lock);

	ret = btrfs_discard_extent(fs_info->extent_root,
				   start, bytes, &trimmed);
	if (!ret)
		*total_trimmed += trimmed;

	mutex_lock(&ctl->cache_writeout_mutex);
	btrfs_add_free_space(block_group, reserved_start, reserved_bytes);
	list_del(&trim_entry->list);
	mutex_unlock(&ctl->cache_writeout_mutex);

	if (update) {
		spin_lock(&space_info->lock);
		spin_lock(&block_group->lock);
		if (block_group->ro)
			space_info->bytes_readonly += reserved_bytes;
		block_group->reserved -= reserved_bytes;
		space_info->bytes_reserved -= reserved_bytes;
		spin_unlock(&space_info->lock);
		spin_unlock(&block_group->lock);
	}

	return ret;
}
