btrfs_resume_dev_replace_async(struct btrfs_fs_info *fs_info)
{
	struct task_struct *task;
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	btrfs_dev_replace_lock(dev_replace);
	switch (dev_replace->replace_state) {
	case BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	case BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		btrfs_dev_replace_unlock(dev_replace);
		return 0;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
		break;
	case BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		dev_replace->replace_state =
			BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED;
		break;
	}
	if (!dev_replace->tgtdev || !dev_replace->tgtdev->bdev) {
		btrfs_info(fs_info, "cannot continue dev_replace, tgtdev is missing");
		btrfs_info(fs_info,
			"you may cancel the operation after 'mount -o degraded'");
		btrfs_dev_replace_unlock(dev_replace);
		return 0;
	}
	btrfs_dev_replace_unlock(dev_replace);

	WARN_ON(atomic_xchg(
		&fs_info->mutually_exclusive_operation_running, 1));
	task = kthread_run(btrfs_dev_replace_kthread, fs_info, "btrfs-devrepl");
	return PTR_ERR_OR_ZERO(task);
}
