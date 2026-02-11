squashfs_xattr_handler_get(const struct xattr_handler *handler,
				      struct dentry *d, const char *name,
				      void *buffer, size_t size)
{
	if (name[0] == '\0')
		return  -EINVAL;

	return squashfs_xattr_get(d_inode(d), handler->flags, name,
		buffer, size);
}
