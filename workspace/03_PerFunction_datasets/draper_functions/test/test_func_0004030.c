dev_mkdir(const char *name, umode_t mode)
{
	struct dentry *dentry;
	struct path path;
	int err;

	dentry = kern_path_create(AT_FDCWD, name, &path, LOOKUP_DIRECTORY);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);

	err = vfs_mkdir(d_inode(path.dentry), dentry, mode);
	if (!err)

		d_inode(dentry)->i_private = &thread;
	done_path_create(&path, dentry);
	return err;
}
