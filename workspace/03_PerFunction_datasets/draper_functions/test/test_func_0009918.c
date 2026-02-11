ocfs2_truncate_log_worker(struct work_struct *work)
{
	int status;
	struct ocfs2_super *osb =
		container_of(work, struct ocfs2_super,
			     osb_truncate_log_wq.work);

	status = ocfs2_flush_truncate_log(osb);
	if (status < 0)
		mlog_errno(status);
	else
		ocfs2_init_steal_slots(osb);
}
