__exclude_logged_extent(struct btrfs_root *root, u64 start, u64 num_bytes)
{
	int ret;
	struct btrfs_block_group_cache *block_group;
	struct btrfs_caching_control *caching_ctl;

	block_group = btrfs_lookup_block_group(root->fs_info, start);
	if (!block_group)
		return -EINVAL;

	cache_block_group(block_group, 0);
	caching_ctl = get_caching_control(block_group);

	if (!caching_ctl) {

		BUG_ON(!block_group_cache_done(block_group));
		ret = btrfs_remove_free_space(block_group, start, num_bytes);
	} else {
		mutex_lock(&caching_ctl->mutex);

		if (start >= caching_ctl->progress) {
			ret = add_excluded_extent(root, start, num_bytes);
		} else if (start + num_bytes <= caching_ctl->progress) {
			ret = btrfs_remove_free_space(block_group,
						      start, num_bytes);
		} else {
			num_bytes = caching_ctl->progress - start;
			ret = btrfs_remove_free_space(block_group,
						      start, num_bytes);
			if (ret)
				goto out_lock;

			num_bytes = (start + num_bytes) -
				caching_ctl->progress;
			start = caching_ctl->progress;
			ret = add_excluded_extent(root, start, num_bytes);
		}
out_lock:
		mutex_unlock(&caching_ctl->mutex);
		put_caching_control(caching_ctl);
	}
	btrfs_put_block_group(block_group);
	return ret;
}
