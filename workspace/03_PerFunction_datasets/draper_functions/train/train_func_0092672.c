xfs_rtmodify_summary_int(
	xfs_mount_t	*mp,
	xfs_trans_t	*tp,
	int		log,
	xfs_rtblock_t	bbno,
	int		delta,
	xfs_buf_t	**rbpp,
	xfs_fsblock_t	*rsb,
	xfs_suminfo_t	*sum)
{
	xfs_buf_t	*bp;
	int		error;
	xfs_fsblock_t	sb;
	int		so;
	xfs_suminfo_t	*sp;


	so = XFS_SUMOFFS(mp, log, bbno);


	sb = XFS_SUMOFFSTOBLOCK(mp, so);


	if (*rbpp && *rsb == sb)
		bp = *rbpp;


	else {


		if (*rbpp)
			xfs_trans_brelse(tp, *rbpp);
		error = xfs_rtbuf_get(mp, tp, sb, 1, &bp);
		if (error) {
			return error;
		}


		*rbpp = bp;
		*rsb = sb;
	}


	sp = XFS_SUMPTR(mp, bp, so);
	if (delta) {
		uint first = (uint)((char *)sp - (char *)bp->b_addr);

		*sp += delta;
		xfs_trans_log_buf(tp, bp, first, first + sizeof(*sp) - 1);
	}
	if (sum)
		*sum = *sp;
	return 0;
}
