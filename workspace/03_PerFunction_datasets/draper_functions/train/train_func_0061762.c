nilfs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct inode *inode = file_inode(filp);
	void __user *argp = (void __user *)arg;

	switch (cmd) {
	case FS_IOC_GETFLAGS:
		return nilfs_ioctl_getflags(inode, argp);
	case FS_IOC_SETFLAGS:
		return nilfs_ioctl_setflags(inode, filp, argp);
	case FS_IOC_GETVERSION:
		return nilfs_ioctl_getversion(inode, argp);
	case NILFS_IOCTL_CHANGE_CPMODE:
		return nilfs_ioctl_change_cpmode(inode, filp, cmd, argp);
	case NILFS_IOCTL_DELETE_CHECKPOINT:
		return nilfs_ioctl_delete_checkpoint(inode, filp, cmd, argp);
	case NILFS_IOCTL_GET_CPINFO:
		return nilfs_ioctl_get_info(inode, filp, cmd, argp,
					    sizeof(struct nilfs_cpinfo),
					    nilfs_ioctl_do_get_cpinfo);
	case NILFS_IOCTL_GET_CPSTAT:
		return nilfs_ioctl_get_cpstat(inode, filp, cmd, argp);
	case NILFS_IOCTL_GET_SUINFO:
		return nilfs_ioctl_get_info(inode, filp, cmd, argp,
					    sizeof(struct nilfs_suinfo),
					    nilfs_ioctl_do_get_suinfo);
	case NILFS_IOCTL_SET_SUINFO:
		return nilfs_ioctl_set_suinfo(inode, filp, cmd, argp);
	case NILFS_IOCTL_GET_SUSTAT:
		return nilfs_ioctl_get_sustat(inode, filp, cmd, argp);
	case NILFS_IOCTL_GET_VINFO:
		return nilfs_ioctl_get_info(inode, filp, cmd, argp,
					    sizeof(struct nilfs_vinfo),
					    nilfs_ioctl_do_get_vinfo);
	case NILFS_IOCTL_GET_BDESCS:
		return nilfs_ioctl_get_bdescs(inode, filp, cmd, argp);
	case NILFS_IOCTL_CLEAN_SEGMENTS:
		return nilfs_ioctl_clean_segments(inode, filp, cmd, argp);
	case NILFS_IOCTL_SYNC:
		return nilfs_ioctl_sync(inode, filp, cmd, argp);
	case NILFS_IOCTL_RESIZE:
		return nilfs_ioctl_resize(inode, filp, argp);
	case NILFS_IOCTL_SET_ALLOC_RANGE:
		return nilfs_ioctl_set_alloc_range(inode, argp);
	case FITRIM:
		return nilfs_ioctl_trim_fs(inode, argp);
	default:
		return -ENOTTY;
	}
}
