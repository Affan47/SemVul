xfs_ioc_getbmapx(
	struct xfs_inode	*ip,
	void			__user *arg)
{
	struct getbmapx		bmx;
	int			error;

	if (copy_from_user(&bmx, arg, sizeof(bmx)))
		return -EFAULT;

	if (bmx.bmv_count < 2)
		return -EINVAL;

	if (bmx.bmv_iflags & (~BMV_IF_VALID))
		return -EINVAL;

	error = xfs_getbmap(ip, &bmx, xfs_getbmapx_format,
			    (__force struct getbmapx *)arg+1);
	if (error)
		return error;


	if (copy_to_user(arg, &bmx, sizeof(struct getbmapx)))
		return -EFAULT;

	return 0;
}
