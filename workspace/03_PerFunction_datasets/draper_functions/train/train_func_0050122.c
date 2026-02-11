vfs_listxattr(struct dentry *d, char *list, size_t size)
{
	ssize_t error;

	error = security_inode_listxattr(d);
	if (error)
		return error;
	error = -EOPNOTSUPP;
	if (d->d_inode->i_op->listxattr) {
		error = d->d_inode->i_op->listxattr(d, list, size);
	} else {
		error = security_inode_listsecurity(d->d_inode, list, size);
		if (size && error > size)
			error = -ERANGE;
	}
	return error;
}
