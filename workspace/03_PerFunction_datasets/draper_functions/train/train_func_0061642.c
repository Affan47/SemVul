btrfs_getxattr(struct dentry *dentry, const char *name,
		       void *buffer, size_t size)
{
	int ret;


	if (!strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return generic_getxattr(dentry, name, buffer, size);

	ret = btrfs_is_valid_xattr(name);
	if (ret)
		return ret;
	return __btrfs_getxattr(d_inode(dentry), name, buffer, size);
}
