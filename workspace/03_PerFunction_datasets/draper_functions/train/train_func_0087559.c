ocfs2_qinfo_lock(struct ocfs2_mem_dqinfo *oinfo, int ex)
{
	struct ocfs2_lock_res *lockres = &oinfo->dqi_gqlock;
	struct ocfs2_super *osb = OCFS2_SB(oinfo->dqi_gi.dqi_sb);
	int level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	int status = 0;


	if (ocfs2_is_hard_readonly(osb)) {
		if (ex)
			status = -EROFS;
		goto bail;
	}
	if (ocfs2_mount_local(osb))
		goto bail;

	status = ocfs2_cluster_lock(osb, lockres, level, 0, 0);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	if (!ocfs2_should_refresh_lock_res(lockres))
		goto bail;

	status = ocfs2_refresh_qinfo(oinfo);
	if (status)
		ocfs2_qinfo_unlock(oinfo, ex);
	ocfs2_complete_lock_res_refresh(lockres, status);
bail:
	return status;
}
