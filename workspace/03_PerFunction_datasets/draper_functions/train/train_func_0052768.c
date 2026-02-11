remove_dir(struct dentry * d)
{
	struct dentry * parent = dget(d->d_parent);
	struct configfs_dirent * sd;

	sd = d->d_fsdata;
	spin_lock(&configfs_dirent_lock);
	list_del_init(&sd->s_sibling);
	spin_unlock(&configfs_dirent_lock);
	configfs_put(sd);
	if (d_really_is_positive(d))
		simple_rmdir(d_inode(parent),d);

	pr_debug(" o %pd removing done (%d)\n", d, d_count(d));

	dput(parent);
}
