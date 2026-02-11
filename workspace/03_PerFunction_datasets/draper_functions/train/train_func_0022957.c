v9fs_inode_from_fid(struct v9fs_session_info *v9ses, struct p9_fid *fid,
		    struct super_block *sb, int new)
{
	struct p9_wstat *st;
	struct inode *inode = NULL;

	st = p9_client_stat(fid);
	if (IS_ERR(st))
		return ERR_CAST(st);

	inode = v9fs_qid_iget(sb, &st->qid, st, new);
	p9stat_free(st);
	kfree(st);
	return inode;
}
