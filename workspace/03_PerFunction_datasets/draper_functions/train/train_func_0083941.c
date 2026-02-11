adfs_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	struct inode *inode = NULL;
	struct object_info obj;
	int error;

	error = adfs_dir_lookup_byname(dir, &dentry->d_name, &obj);
	if (error == 0) {
		error = -EACCES;


		inode = adfs_iget(dir->i_sb, &obj);
		if (inode)
			error = 0;
	}
	d_add(dentry, inode);
	return ERR_PTR(error);
}
