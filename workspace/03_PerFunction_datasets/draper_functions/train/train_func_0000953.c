v9fs_fid_clone(struct dentry *dentry)
{
	struct p9_fid *fid, *ret;

	fid = v9fs_fid_lookup(dentry);
	if (IS_ERR(fid))
		return fid;

	ret = p9_client_walk(fid, 0, NULL, 1);
	return ret;
}
