xfs_btree_readahead(
	struct xfs_btree_cur	*cur,
	int			lev,
	int			lr)
{
	struct xfs_btree_block	*block;


	if ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    (lev == cur->bc_nlevels - 1))
		return 0;

	if ((cur->bc_ra[lev] | lr) == cur->bc_ra[lev])
		return 0;

	cur->bc_ra[lev] |= lr;
	block = XFS_BUF_TO_BLOCK(cur->bc_bufs[lev]);

	if (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		return xfs_btree_readahead_lblock(cur, lr, block);
	return xfs_btree_readahead_sblock(cur, lr, block);
}
