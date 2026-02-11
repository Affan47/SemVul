kernfs_refresh_inode(struct kernfs_node *kn, struct inode *inode)
{
	struct kernfs_iattrs *attrs = kn->iattr;

	inode->i_mode = kn->mode;
	if (attrs) {


		set_inode_attr(inode, &attrs->ia_iattr);
		security_inode_notifysecctx(inode, attrs->ia_secdata,
					    attrs->ia_secdata_len);
	}

	if (kernfs_type(kn) == KERNFS_DIR)
		set_nlink(inode, kn->dir.subdirs + 2);
}
