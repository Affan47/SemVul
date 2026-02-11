hfsplus_rename(struct inode *old_dir, struct dentry *old_dentry,
			  struct inode *new_dir, struct dentry *new_dentry)
{
	int res;


	if (d_really_is_positive(new_dentry)) {
		if (d_is_dir(new_dentry))
			res = hfsplus_rmdir(new_dir, new_dentry);
		else
			res = hfsplus_unlink(new_dir, new_dentry);
		if (res)
			return res;
	}

	res = hfsplus_rename_cat((u32)(unsigned long)old_dentry->d_fsdata,
				 old_dir, &old_dentry->d_name,
				 new_dir, &new_dentry->d_name);
	if (!res)
		new_dentry->d_fsdata = old_dentry->d_fsdata;
	return res;
}
