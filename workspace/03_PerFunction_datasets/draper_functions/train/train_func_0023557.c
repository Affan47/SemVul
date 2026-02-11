xfs_log_regrant(
	struct xfs_mount	*mp,
	struct xlog_ticket	*tic)
{
	struct xlog		*log = mp->m_log;
	int			need_bytes;
	int			error = 0;

	if (XLOG_FORCED_SHUTDOWN(log))
		return -EIO;

	XFS_STATS_INC(mp, xs_try_logspace);


	tic->t_tid++;

	xlog_grant_push_ail(log, tic->t_unit_res);

	tic->t_curr_res = tic->t_unit_res;
	xlog_tic_reset_res(tic);

	if (tic->t_cnt > 0)
		return 0;

	trace_xfs_log_regrant(log, tic);

	error = xlog_grant_head_check(log, &log->l_write_head, tic,
				      &need_bytes);
	if (error)
		goto out_error;

	xlog_grant_add_space(log, &log->l_write_head.grant, need_bytes);
	trace_xfs_log_regrant_exit(log, tic);
	xlog_verify_grant_tail(log);
	return 0;

out_error:


	tic->t_curr_res = 0;
	tic->t_cnt = 0;
	return error;
}
