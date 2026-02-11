xfs_xattr_set(const struct xattr_handler *handler, struct dentry *dentry,
		const char *name, const void *value, size_t size, int flags)
{
	int			xflags = handler->flags;
	struct xfs_inode	*ip = XFS_I(d_inode(dentry));
	int			error;

	if (strcmp(name, "") == 0)
		return -EINVAL;


	if (flags & XATTR_CREATE)
		xflags |= ATTR_CREATE;
	if (flags & XATTR_REPLACE)
		xflags |= ATTR_REPLACE;

	if (!value)
		return xfs_attr_remove(ip, (unsigned char *)name, xflags);
	error = xfs_attr_set(ip, (unsigned char *)name,
				(void *)value, size, xflags);
	if (!error)
		xfs_forget_acl(d_inode(dentry), name, xflags);

	return error;
}
