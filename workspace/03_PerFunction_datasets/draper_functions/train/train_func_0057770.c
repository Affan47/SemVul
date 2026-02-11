exportfs_encode_fh(struct dentry *dentry, struct fid *fid, int *max_len,
		int connectable)
{
	int error;
	struct dentry *p = NULL;
	struct inode *inode = dentry->d_inode, *parent = NULL;

	if (connectable && !S_ISDIR(inode->i_mode)) {
		p = dget_parent(dentry);


		parent = p->d_inode;
	}

	error = exportfs_encode_inode_fh(inode, fid, max_len, parent);
	dput(p);

	return error;
}
