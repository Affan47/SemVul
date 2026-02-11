xfs_dir3_leaf_log_bests(
	struct xfs_da_args	*args,
	struct xfs_buf		*bp,
	int			first,
	int			last)
{
	__be16			*firstb;
	__be16			*lastb;
	struct xfs_dir2_leaf	*leaf = bp->b_addr;
	xfs_dir2_leaf_tail_t	*ltp;

	ASSERT(leaf->hdr.info.magic == cpu_to_be16(XFS_DIR2_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_DIR3_LEAF1_MAGIC));

	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	firstb = xfs_dir2_leaf_bests_p(ltp) + first;
	lastb = xfs_dir2_leaf_bests_p(ltp) + last;
	xfs_trans_log_buf(args->trans, bp,
		(uint)((char *)firstb - (char *)leaf),
		(uint)((char *)lastb - (char *)leaf + sizeof(*lastb) - 1));
}
