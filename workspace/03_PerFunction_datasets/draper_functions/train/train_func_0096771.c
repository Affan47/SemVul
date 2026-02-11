xfs_trans_mod_dquot(
	xfs_trans_t	*tp,
	xfs_dquot_t	*dqp,
	uint		field,
	long		delta)
{
	xfs_dqtrx_t	*qtrx;

	ASSERT(tp);
	ASSERT(XFS_IS_QUOTA_RUNNING(tp->t_mountp));
	qtrx = NULL;

	if (tp->t_dqinfo == NULL)
		xfs_trans_alloc_dqinfo(tp);


	qtrx = xfs_trans_get_dqtrx(tp, dqp);
	ASSERT(qtrx);
	if (qtrx->qt_dquot == NULL)
		qtrx->qt_dquot = dqp;

	switch (field) {


	      case XFS_TRANS_DQ_RES_BLKS:
		qtrx->qt_blk_res += (ulong)delta;
		break;


	      case XFS_TRANS_DQ_RES_INOS:
		qtrx->qt_ino_res += (ulong)delta;
		break;


	      case XFS_TRANS_DQ_BCOUNT:
		qtrx->qt_bcount_delta += delta;
		break;

	      case XFS_TRANS_DQ_DELBCOUNT:
		qtrx->qt_delbcnt_delta += delta;
		break;


	      case XFS_TRANS_DQ_ICOUNT:
		if (qtrx->qt_ino_res && delta > 0) {
			qtrx->qt_ino_res_used += (ulong)delta;
			ASSERT(qtrx->qt_ino_res >= qtrx->qt_ino_res_used);
		}
		qtrx->qt_icount_delta += delta;
		break;


	      case XFS_TRANS_DQ_RES_RTBLKS:
		qtrx->qt_rtblk_res += (ulong)delta;
		break;


	      case XFS_TRANS_DQ_RTBCOUNT:
		if (qtrx->qt_rtblk_res && delta > 0) {
			qtrx->qt_rtblk_res_used += (ulong)delta;
			ASSERT(qtrx->qt_rtblk_res >= qtrx->qt_rtblk_res_used);
		}
		qtrx->qt_rtbcount_delta += delta;
		break;

	      case XFS_TRANS_DQ_DELRTBCOUNT:
		qtrx->qt_delrtb_delta += delta;
		break;

	      default:
		ASSERT(0);
	}
	tp->t_flags |= XFS_TRANS_DQ_DIRTY;
}
