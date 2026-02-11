balance_kthread(void *data)
{
	struct btrfs_fs_info *fs_info = data;
	int ret = 0;

	mutex_lock(&fs_info->volume_mutex);
	mutex_lock(&fs_info->balance_mutex);

	if (fs_info->balance_ctl) {
		btrfs_info(fs_info, "continuing balance");
		ret = btrfs_balance(fs_info->balance_ctl, NULL);
	}

	mutex_unlock(&fs_info->balance_mutex);
	mutex_unlock(&fs_info->volume_mutex);

	return ret;
}
