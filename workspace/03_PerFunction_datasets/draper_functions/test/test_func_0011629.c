ceph_getxattr(struct dentry *dentry, const char *name, void *value,
		      size_t size)
{
	if (!strncmp(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		return generic_getxattr(dentry, name, value, size);

	return __ceph_getxattr(d_inode(dentry), name, value, size);
}
