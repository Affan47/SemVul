configfs_make_dirent(struct configfs_dirent * parent_sd,
			 struct dentry * dentry, void * element,
			 umode_t mode, int type)
{
	struct configfs_dirent * sd;

	sd = configfs_new_dirent(parent_sd, element, type);
	if (IS_ERR(sd))
		return PTR_ERR(sd);

	sd->s_mode = mode;
	sd->s_dentry = dentry;
	if (dentry)
		dentry->d_fsdata = configfs_get(sd);

	return 0;
}
