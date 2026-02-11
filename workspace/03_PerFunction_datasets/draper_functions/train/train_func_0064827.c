xfs_sync_sb(
	struct xfs_mount	*mp,
	bool			wait)
{
	struct xfs_trans	*tp;
	int			error;

	tp = _xfs_trans_alloc(mp, XFS_TRANS_SB_CHANGE, KM_SLEEP);
	error = xfs_trans_reserve(tp, &M_RES(mp)->tr_sb, 0, 0);
	if (error) {
		xfs_trans_cancel(tp);
		return error;
	}

	xfs_log_sb(tp);
	if (wait)
		xfs_trans_set_sync(tp);
	return xfs_trans_commit(tp);
}
