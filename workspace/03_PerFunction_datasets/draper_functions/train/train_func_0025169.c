xfs_trans_free_items(
	struct xfs_trans	*tp,
	xfs_lsn_t		commit_lsn,
	bool			abort)
{
	struct xfs_log_item_desc *lidp, *next;

	list_for_each_entry_safe(lidp, next, &tp->t_items, lid_trans) {
		struct xfs_log_item	*lip = lidp->lid_item;

		lip->li_desc = NULL;

		if (commit_lsn != NULLCOMMITLSN)
			lip->li_ops->iop_committing(lip, commit_lsn);
		if (abort)
			lip->li_flags |= XFS_LI_ABORTED;
		lip->li_ops->iop_unlock(lip);

		xfs_trans_free_item_desc(lidp);
	}
}
