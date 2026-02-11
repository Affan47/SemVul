v9fs_lookup_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct p9_fid *fid;
	struct inode *inode;
	struct v9fs_inode *v9inode;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	inode = d_inode(dentry);
	if (!inode)
		goto out_valid;

	v9inode = V9FS_I(inode);
	if (v9inode->cache_validity & V9FS_INO_INVALID_ATTR) {
		int retval;
		struct v9fs_session_info *v9ses;
		fid = v9fs_fid_lookup(dentry);
		if (IS_ERR(fid))
			return PTR_ERR(fid);

		v9ses = v9fs_inode2v9ses(inode);
		if (v9fs_proto_dotl(v9ses))
			retval = v9fs_refresh_inode_dotl(fid, inode);
		else
			retval = v9fs_refresh_inode(fid, inode);
		if (retval == -ENOENT)
			return 0;
		if (retval < 0)
			return retval;
	}
out_valid:
	return 1;
}
