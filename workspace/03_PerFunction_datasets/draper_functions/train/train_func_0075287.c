f2fs_xattr_advise_get(const struct xattr_handler *handler,
		struct dentry *dentry, const char *name, void *buffer,
		size_t size)
{
	struct inode *inode = d_inode(dentry);

	if (strcmp(name, "") != 0)
		return -EINVAL;

	if (buffer)
		*((char *)buffer) = F2FS_I(inode)->i_advise;
	return sizeof(char);
}
