v9fs_drop_inode(struct inode *inode)
{
	struct v9fs_session_info *v9ses;
	v9ses = v9fs_inode2v9ses(inode);
	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		return generic_drop_inode(inode);


	return 1;
}
