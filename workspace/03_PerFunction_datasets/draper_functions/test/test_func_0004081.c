xfs_allocbt_key_diff(
	struct xfs_btree_cur	*cur,
	union xfs_btree_key	*key)
{
	xfs_alloc_rec_incore_t	*rec = &cur->bc_rec.a;
	xfs_alloc_key_t		*kp = &key->alloc;
	__int64_t		diff;

	if (cur->bc_btnum == XFS_BTNUM_BNO) {
		return (__int64_t)be32_to_cpu(kp->ar_startblock) -
				rec->ar_startblock;
	}

	diff = (__int64_t)be32_to_cpu(kp->ar_blockcount) - rec->ar_blockcount;
	if (diff)
		return diff;

	return (__int64_t)be32_to_cpu(kp->ar_startblock) - rec->ar_startblock;
}
