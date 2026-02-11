ocfs2_rw_lock(struct inode *inode, int write)
{
	int status, level;
	struct ocfs2_lock_res *lockres;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	BUG_ON(!inode);

	mlog(0, "inode %llu take %s RW lock\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno,
	     write ? "EXMODE" : "PRMODE");

	if (ocfs2_mount_local(osb))
		return 0;

	lockres = &OCFS2_I(inode)->ip_rw_lockres;

	level = write ? DLM_LOCK_EX : DLM_LOCK_PR;

	status = ocfs2_cluster_lock(OCFS2_SB(inode->i_sb), lockres, level, 0,
				    0);
	if (status < 0)
		mlog_errno(status);

	return status;
}
