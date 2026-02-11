shmem_whiteout(struct inode *old_dir, struct dentry *old_dentry)
{
	struct dentry *whiteout;
	int error;

	whiteout = d_alloc(old_dentry->d_parent, &old_dentry->d_name);
	if (!whiteout)
		return -ENOMEM;

	error = shmem_mknod(old_dir, whiteout,
			    S_IFCHR | WHITEOUT_MODE, WHITEOUT_DEV);
	dput(whiteout);
	if (error)
		return error;


	d_rehash(whiteout);
	return 0;
}
