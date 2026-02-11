fuse_ctl_remove_conn(struct fuse_conn *fc)
{
	int i;

	if (!fuse_control_sb)
		return;

	for (i = fc->ctl_ndents - 1; i >= 0; i--) {
		struct dentry *dentry = fc->ctl_dentry[i];
		d_inode(dentry)->i_private = NULL;
		d_drop(dentry);
		dput(dentry);
	}
	drop_nlink(d_inode(fuse_control_sb->s_root));
}
