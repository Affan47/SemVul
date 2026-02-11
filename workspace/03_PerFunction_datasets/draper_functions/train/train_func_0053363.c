xfs_btree_setbuf(
	xfs_btree_cur_t		*cur,
	int			lev,
	xfs_buf_t		*bp)
{
	struct xfs_btree_block	*b;

	if (cur->bc_bufs[lev])
		xfs_trans_brelse(cur->bc_tp, cur->bc_bufs[lev]);
	cur->bc_bufs[lev] = bp;
	cur->bc_ra[lev] = 0;

	b = XFS_BUF_TO_BLOCK(bp);
	if (cur->bc_flags & XFS_BTREE_LONG_PTRS) {
		if (b->bb_u.l.bb_leftsib == cpu_to_be64(NULLFSBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_LEFTRA;
		if (b->bb_u.l.bb_rightsib == cpu_to_be64(NULLFSBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_RIGHTRA;
	} else {
		if (b->bb_u.s.bb_leftsib == cpu_to_be32(NULLAGBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_LEFTRA;
		if (b->bb_u.s.bb_rightsib == cpu_to_be32(NULLAGBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_RIGHTRA;
	}
}
