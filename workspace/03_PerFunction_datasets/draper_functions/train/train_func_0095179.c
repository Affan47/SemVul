xfs_btree_lookup_get_block(
	struct xfs_btree_cur	*cur,
	int			level,
	union xfs_btree_ptr	*pp,
	struct xfs_btree_block	**blkp)
{
	struct xfs_buf		*bp;
	int			error = 0;


	if ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    (level == cur->bc_nlevels - 1)) {
		*blkp = xfs_btree_get_iroot(cur);
		return 0;
	}


	bp = cur->bc_bufs[level];
	if (bp && XFS_BUF_ADDR(bp) == xfs_btree_ptr_to_daddr(cur, pp)) {
		*blkp = XFS_BUF_TO_BLOCK(bp);
		return 0;
	}

	error = xfs_btree_read_buf_block(cur, pp, 0, blkp, &bp);
	if (error)
		return error;

	xfs_btree_setbuf(cur, level, bp);
	return 0;
}
