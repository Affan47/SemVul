do_open_dir(struct file *file, int flags, struct file *h_file)
{
	int err;
	aufs_bindex_t bindex, btail;
	struct dentry *dentry, *h_dentry;

	FiMustWriteLock(file);
	AuDebugOn(h_file);

	err = 0;
	dentry = file->f_path.dentry;
	file->f_version = d_inode(dentry)->i_version;
	bindex = au_dbstart(dentry);
	au_set_fbstart(file, bindex);
	btail = au_dbtaildir(dentry);
	au_set_fbend_dir(file, btail);
	for (; !err && bindex <= btail; bindex++) {
		h_dentry = au_h_dptr(dentry, bindex);
		if (!h_dentry)
			continue;

		h_file = au_h_open(dentry, bindex, flags, file, 0);
		if (IS_ERR(h_file)) {
			err = PTR_ERR(h_file);
			break;
		}
		au_set_h_fptr(file, bindex, h_file);
	}
	au_update_figen(file);


	if (!err)
		return 0;


	for (bindex = au_fbstart(file); bindex <= btail; bindex++)
		au_set_h_fptr(file, bindex, NULL);
	au_set_fbstart(file, -1);
	au_set_fbend_dir(file, -1);

	return err;
}
