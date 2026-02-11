ocfs2_match_dentry(struct dentry *dentry,
			      u64 parent_blkno,
			      int skip_unhashed)
{
	struct inode *parent;


	if (!dentry->d_fsdata)
		return 0;

	if (!dentry->d_parent)
		return 0;

	if (skip_unhashed && d_unhashed(dentry))
		return 0;

	parent = d_inode(dentry->d_parent);

	if (!parent)
		return 0;


	if (OCFS2_I(parent)->ip_blkno != parent_blkno)
		return 0;

	return 1;
}
