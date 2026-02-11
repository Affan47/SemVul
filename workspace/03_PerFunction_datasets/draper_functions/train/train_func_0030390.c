xfs_quota_need_throttle(
	struct xfs_inode *ip,
	int type,
	xfs_fsblock_t alloc_blocks)
{
	struct xfs_dquot *dq = xfs_inode_dquot(ip, type);

	if (!dq || !xfs_this_quota_on(ip->i_mount, type))
		return false;


	if (!dq->q_prealloc_hi_wmark)
		return false;


	if (dq->q_res_bcount + alloc_blocks < dq->q_prealloc_lo_wmark)
		return false;

	return true;
}
