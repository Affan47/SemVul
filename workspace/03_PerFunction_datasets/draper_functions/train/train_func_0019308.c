xfs_qm_dqpurge(
	struct xfs_dquot	*dqp,
	void			*data)
{
	struct xfs_mount	*mp = dqp->q_mount;
	struct xfs_quotainfo	*qi = mp->m_quotainfo;

	xfs_dqlock(dqp);
	if ((dqp->dq_flags & XFS_DQ_FREEING) || dqp->q_nrefs != 0) {
		xfs_dqunlock(dqp);
		return -EAGAIN;
	}

	dqp->dq_flags |= XFS_DQ_FREEING;

	xfs_dqflock(dqp);


	if (XFS_DQ_IS_DIRTY(dqp)) {
		struct xfs_buf	*bp = NULL;
		int		error;


		error = xfs_qm_dqflush(dqp, &bp);
		if (error) {
			xfs_warn(mp, "%s: dquot %p flush failed",
				__func__, dqp);
		} else {
			error = xfs_bwrite(bp);
			xfs_buf_relse(bp);
		}
		xfs_dqflock(dqp);
	}

	ASSERT(atomic_read(&dqp->q_pincount) == 0);
	ASSERT(XFS_FORCED_SHUTDOWN(mp) ||
	       !(dqp->q_logitem.qli_item.li_flags & XFS_LI_IN_AIL));

	xfs_dqfunlock(dqp);
	xfs_dqunlock(dqp);

	radix_tree_delete(xfs_dquot_tree(qi, dqp->q_core.d_flags),
			  be32_to_cpu(dqp->q_core.d_id));
	qi->qi_dquots--;


	ASSERT(!list_empty(&dqp->q_lru));
	list_lru_del(&qi->qi_lru, &dqp->q_lru);
	XFS_STATS_DEC(mp, xs_qm_dquot_unused);

	xfs_qm_dqdestroy(dqp);
	return 0;
}
