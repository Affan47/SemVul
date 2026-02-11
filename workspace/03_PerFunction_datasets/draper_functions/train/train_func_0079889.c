security_path_rmdir(struct path *dir, struct dentry *dentry)
{
	if (unlikely(IS_PRIVATE(d_backing_inode(dir->dentry))))
		return 0;
	return call_int_hook(path_rmdir, 0, dir, dentry);
}
