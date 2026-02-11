btrfs_rm_dev_replace_free_srcdev(struct btrfs_fs_info *fs_info,
				      struct btrfs_device *srcdev)
{
	struct btrfs_fs_devices *fs_devices = srcdev->fs_devices;

	call_rcu(&srcdev->rcu, free_device);


	BUG_ON(!fs_devices->num_devices && !fs_devices->seeding);


	if (!fs_devices->num_devices) {
		struct btrfs_fs_devices *tmp_fs_devices;

		tmp_fs_devices = fs_info->fs_devices;
		while (tmp_fs_devices) {
			if (tmp_fs_devices->seed == fs_devices) {
				tmp_fs_devices->seed = fs_devices->seed;
				break;
			}
			tmp_fs_devices = tmp_fs_devices->seed;
		}
		fs_devices->seed = NULL;
		__btrfs_close_devices(fs_devices);
		free_fs_devices(fs_devices);
	}
}
