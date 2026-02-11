vfsub_lookup_one_len(const char *name, struct dentry *parent,
				    int len)
{
	struct path path = {
		.mnt = NULL
	};


	IMustLock(d_inode(parent));

	path.dentry = lookup_one_len(name, parent, len);
	if (IS_ERR(path.dentry))
		goto out;
	if (d_is_positive(path.dentry))
		vfsub_update_h_iattr(&path, NULL);

out:
	AuTraceErrPtr(path.dentry);
	return path.dentry;
}
