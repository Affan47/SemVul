xfs_qm_dqread(
	struct xfs_mount	*mp,
	xfs_dqid_t		id,
	uint			type,
	uint			flags,
	struct xfs_dquot	**O_dqpp)
{
	struct xfs_dquot	*dqp;
	struct xfs_disk_dquot	*ddqp;
	struct xfs_buf		*bp;
	struct xfs_trans	*tp = NULL;
	int			error;

	dqp = kmem_zone_zalloc(xfs_qm_dqzone, KM_SLEEP);

	dqp->dq_flags = type;
	dqp->q_core.d_id = cpu_to_be32(id);
	dqp->q_mount = mp;
	INIT_LIST_HEAD(&dqp->q_lru);
	mutex_init(&dqp->q_qlock);
	init_waitqueue_head(&dqp->q_pinwait);


	init_completion(&dqp->q_flush);
	complete(&dqp->q_flush);


	switch (type) {
	case XFS_DQ_USER:

		break;
	case XFS_DQ_GROUP:
		lockdep_set_class(&dqp->q_qlock, &xfs_dquot_group_class);
		break;
	case XFS_DQ_PROJ:
		lockdep_set_class(&dqp->q_qlock, &xfs_dquot_project_class);
		break;
	default:
		ASSERT(0);
		break;
	}

	XFS_STATS_INC(mp, xs_qm_dquot);

	trace_xfs_dqread(dqp);

	if (flags & XFS_QMOPT_DQALLOC) {
		tp = xfs_trans_alloc(mp, XFS_TRANS_QM_DQALLOC);
		error = xfs_trans_reserve(tp, &M_RES(mp)->tr_qm_dqalloc,
					  XFS_QM_DQALLOC_SPACE_RES(mp), 0);
		if (error)
			goto error1;
	}


	error = xfs_qm_dqtobp(&tp, dqp, &ddqp, &bp, flags);
	if (error) {


		trace_xfs_dqread_fail(dqp);
		goto error1;
	}


	memcpy(&dqp->q_core, ddqp, sizeof(xfs_disk_dquot_t));
	xfs_qm_dquot_logitem_init(dqp);


	dqp->q_res_bcount = be64_to_cpu(ddqp->d_bcount);
	dqp->q_res_icount = be64_to_cpu(ddqp->d_icount);
	dqp->q_res_rtbcount = be64_to_cpu(ddqp->d_rtbcount);


	xfs_dquot_set_prealloc_limits(dqp);


	xfs_buf_set_ref(bp, XFS_DQUOT_REF);


	ASSERT(xfs_buf_islocked(bp));
	xfs_trans_brelse(tp, bp);

	if (tp) {
		error = xfs_trans_commit(tp);
		if (error)
			goto error0;
	}

	*O_dqpp = dqp;
	return error;

error1:
	if (tp)
		xfs_trans_cancel(tp);
error0:
	xfs_qm_dqdestroy(dqp);
	*O_dqpp = NULL;
	return error;
}
