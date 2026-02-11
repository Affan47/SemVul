vfs_getxattr(struct dentry *dentry, const char *name, void *value, size_t size)
{
	struct inode *inode = dentry->d_inode;
	int error;

	error = xattr_permission(inode, name, MAY_READ);
	if (error)
		return error;

	error = security_inode_getxattr(dentry, name);
	if (error)
		return error;

	if (!strncmp(name, XATTR_SECURITY_PREFIX,
				XATTR_SECURITY_PREFIX_LEN)) {
		const char *suffix = name + XATTR_SECURITY_PREFIX_LEN;
		int ret = xattr_getsecurity(inode, suffix, value, size);


		if (ret == -EOPNOTSUPP)
			goto nolsm;
		return ret;
	}
nolsm:
	if (inode->i_op->getxattr)
		error = inode->i_op->getxattr(dentry, name, value, size);
	else
		error = -EOPNOTSUPP;

	return error;
}
