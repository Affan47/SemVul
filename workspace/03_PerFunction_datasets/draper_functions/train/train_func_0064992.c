xfs_trans_ail_delete_bulk(
	struct xfs_ail		*ailp,
	struct xfs_log_item	**log_items,
	int			nr_items,
	int			shutdown_type) __releases(ailp->xa_lock)
{
	xfs_log_item_t		*mlip;
	int			mlip_changed = 0;
	int			i;

	mlip = xfs_ail_min(ailp);

	for (i = 0; i < nr_items; i++) {
		struct xfs_log_item *lip = log_items[i];
		if (!(lip->li_flags & XFS_LI_IN_AIL)) {
			struct xfs_mount	*mp = ailp->xa_mount;

			spin_unlock(&ailp->xa_lock);
			if (!XFS_FORCED_SHUTDOWN(mp)) {
				xfs_alert_tag(mp, XFS_PTAG_AILDELETE,
		"%s: attempting to delete a log item that is not in the AIL",
						__func__);
				xfs_force_shutdown(mp, shutdown_type);
			}
			return;
		}

		trace_xfs_ail_delete(lip, mlip->li_lsn, lip->li_lsn);
		xfs_ail_delete(ailp, lip);
		lip->li_flags &= ~XFS_LI_IN_AIL;
		lip->li_lsn = 0;
		if (mlip == lip)
			mlip_changed = 1;
	}

	if (mlip_changed) {
		if (!XFS_FORCED_SHUTDOWN(ailp->xa_mount))
			xlog_assign_tail_lsn_locked(ailp->xa_mount);
		if (list_empty(&ailp->xa_ail))
			wake_up_all(&ailp->xa_empty);
		spin_unlock(&ailp->xa_lock);

		xfs_log_space_wake(ailp->xa_mount);
	} else {
		spin_unlock(&ailp->xa_lock);
	}
}
