remove_device_files(struct super_block *sb,
			       struct qib_devdata *dd)
{
	struct dentry *dir, *root;
	char unit[10];
	int ret, i;

	root = dget(sb->s_root);
	mutex_lock(&d_inode(root)->i_mutex);
	snprintf(unit, sizeof(unit), "%u", dd->unit);
	dir = lookup_one_len(unit, root, strlen(unit));

	if (IS_ERR(dir)) {
		ret = PTR_ERR(dir);
		pr_err("Lookup of %s failed\n", unit);
		goto bail;
	}

	mutex_lock(&d_inode(dir)->i_mutex);
	remove_file(dir, "counters");
	remove_file(dir, "counter_names");
	remove_file(dir, "portcounter_names");
	for (i = 0; i < dd->num_pports; i++) {
		char fname[24];

		sprintf(fname, "port%dcounters", i + 1);
		remove_file(dir, fname);
		if (dd->flags & QIB_HAS_QSFP) {
			sprintf(fname, "qsfp%d", i + 1);
			remove_file(dir, fname);
		}
	}
	remove_file(dir, "flash");
	mutex_unlock(&d_inode(dir)->i_mutex);
	ret = simple_rmdir(d_inode(root), dir);
	d_delete(dir);
	dput(dir);

bail:
	mutex_unlock(&d_inode(root)->i_mutex);
	dput(root);
	return ret;
}
