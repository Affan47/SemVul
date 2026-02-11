xfs_inobt_free_block(
	struct xfs_btree_cur	*cur,
	struct xfs_buf		*bp)
{
	xfs_fsblock_t		fsbno;
	int			error;

	fsbno = XFS_DADDR_TO_FSB(cur->bc_mp, XFS_BUF_ADDR(bp));
	error = xfs_free_extent(cur->bc_tp, fsbno, 1);
	if (error)
		return error;

	xfs_trans_binval(cur->bc_tp, bp);
	return error;
}
