xlog_do_recover(
	struct xlog	*log,
	xfs_daddr_t	head_blk,
	xfs_daddr_t	tail_blk)
{
	int		error;
	xfs_buf_t	*bp;
	xfs_sb_t	*sbp;


	error = xlog_do_log_recovery(log, head_blk, tail_blk);
	if (error)
		return error;


	if (XFS_FORCED_SHUTDOWN(log->l_mp)) {
		return -EIO;
	}


	xlog_assign_tail_lsn(log->l_mp);


	bp = xfs_getsb(log->l_mp, 0);
	XFS_BUF_UNDONE(bp);
	ASSERT(!(XFS_BUF_ISWRITE(bp)));
	XFS_BUF_READ(bp);
	XFS_BUF_UNASYNC(bp);
	bp->b_ops = &xfs_sb_buf_ops;

	error = xfs_buf_submit_wait(bp);
	if (error) {
		if (!XFS_FORCED_SHUTDOWN(log->l_mp)) {
			xfs_buf_ioerror_alert(bp, __func__);
			ASSERT(0);
		}
		xfs_buf_relse(bp);
		return error;
	}


	sbp = &log->l_mp->m_sb;
	xfs_sb_from_disk(sbp, XFS_BUF_TO_SBP(bp));
	ASSERT(sbp->sb_magicnum == XFS_SB_MAGIC);
	ASSERT(xfs_sb_good_version(sbp));
	xfs_reinit_percpu_counters(log->l_mp);

	xfs_buf_relse(bp);


	xlog_recover_check_summary(log);


	log->l_flags &= ~XLOG_ACTIVE_RECOVERY;
	return 0;
}
