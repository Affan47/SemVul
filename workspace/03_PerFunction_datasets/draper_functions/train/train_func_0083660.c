btrfs_sysfs_remove_fsid(struct btrfs_fs_devices *fs_devs)
{
	struct list_head *fs_uuids = btrfs_get_fs_uuids();

	if (fs_devs) {
		__btrfs_sysfs_remove_fsid(fs_devs);
		return;
	}

	list_for_each_entry(fs_devs, fs_uuids, list) {
		__btrfs_sysfs_remove_fsid(fs_devs);
	}
}
