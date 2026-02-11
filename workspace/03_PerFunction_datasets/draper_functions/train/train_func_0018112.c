ocfs2_sync_fs(struct super_block *sb, int wait)
{
	int status;
	tid_t target;
	struct ocfs2_super *osb = OCFS2_SB(sb);

	if (ocfs2_is_hard_readonly(osb))
		return -EROFS;

	if (wait) {
		status = ocfs2_flush_truncate_log(osb);
		if (status < 0)
			mlog_errno(status);
	} else {
		ocfs2_schedule_truncate_log_flush(osb, 0);
	}

	if (jbd2_journal_start_commit(OCFS2_SB(sb)->journal->j_journal,
				      &target)) {
		if (wait)
			jbd2_log_wait_commit(OCFS2_SB(sb)->journal->j_journal,
					     target);
	}
	return 0;
}
