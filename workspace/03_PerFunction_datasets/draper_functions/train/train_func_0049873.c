xfs_trans_log_dquot(
	xfs_trans_t	*tp,
	xfs_dquot_t	*dqp)
{
	ASSERT(dqp->q_transp == tp);
	ASSERT(XFS_DQ_IS_LOCKED(dqp));

	tp->t_flags |= XFS_TRANS_DIRTY;
	dqp->q_logitem.qli_item.li_desc->lid_flags |= XFS_LID_DIRTY;
}
