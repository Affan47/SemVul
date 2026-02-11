xfs_fs_goingdown(
	xfs_mount_t	*mp,
	__uint32_t	inflags)
{
	switch (inflags) {
	case XFS_FSOP_GOING_FLAGS_DEFAULT: {
		struct super_block *sb = freeze_bdev(mp->m_super->s_bdev);

		if (sb && !IS_ERR(sb)) {
			xfs_force_shutdown(mp, SHUTDOWN_FORCE_UMOUNT);
			thaw_bdev(sb->s_bdev, sb);
		}

		break;
	}
	case XFS_FSOP_GOING_FLAGS_LOGFLUSH:
		xfs_force_shutdown(mp, SHUTDOWN_FORCE_UMOUNT);
		break;
	case XFS_FSOP_GOING_FLAGS_NOLOGFLUSH:
		xfs_force_shutdown(mp,
				SHUTDOWN_FORCE_UMOUNT | SHUTDOWN_LOG_IO_ERROR);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
