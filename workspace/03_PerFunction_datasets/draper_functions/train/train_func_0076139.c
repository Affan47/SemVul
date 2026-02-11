xfs_allocbt_recs_inorder(
	struct xfs_btree_cur	*cur,
	union xfs_btree_rec	*r1,
	union xfs_btree_rec	*r2)
{
	if (cur->bc_btnum == XFS_BTNUM_BNO) {
		return be32_to_cpu(r1->alloc.ar_startblock) +
			be32_to_cpu(r1->alloc.ar_blockcount) <=
			be32_to_cpu(r2->alloc.ar_startblock);
	} else {
		return be32_to_cpu(r1->alloc.ar_blockcount) <
			be32_to_cpu(r2->alloc.ar_blockcount) ||
			(r1->alloc.ar_blockcount == r2->alloc.ar_blockcount &&
			 be32_to_cpu(r1->alloc.ar_startblock) <
			 be32_to_cpu(r2->alloc.ar_startblock));
	}
}
