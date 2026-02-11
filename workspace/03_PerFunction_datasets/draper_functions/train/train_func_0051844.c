xfs_trans_get_qoff_item(
	xfs_trans_t		*tp,
	xfs_qoff_logitem_t	*startqoff,
	uint			flags)
{
	xfs_qoff_logitem_t	*q;

	ASSERT(tp != NULL);

	q = xfs_qm_qoff_logitem_init(tp->t_mountp, startqoff, flags);
	ASSERT(q != NULL);


	xfs_trans_add_item(tp, &q->qql_item);
	return q;
}
