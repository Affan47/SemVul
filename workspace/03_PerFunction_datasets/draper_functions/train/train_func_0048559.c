ioctl_is_mounted(const char *path, unsigned int type)
{
	struct ioctl_ops *ops = get_ioctl_ops();
	unsigned int mounted;

	ops->ismountpoint(LOGOPT_NONE, -1, path, &mounted);
	if (mounted) {
		switch (type) {
		case MNTS_ALL:
			return 1;
		case MNTS_AUTOFS:
			return (mounted & DEV_IOCTL_IS_AUTOFS);
		case MNTS_REAL:
			return (mounted & DEV_IOCTL_IS_OTHER);
		}
	}
	return 0;
}
