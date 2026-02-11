xfs_qm_dqrepair(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	struct xfs_dquot	*dqp,
	xfs_dqid_t		firstid,
	struct xfs_buf		**bpp)
{
	int			error;
	struct xfs_disk_dquot	*ddq;
	struct xfs_dqblk	*d;
	int			i;


	error = xfs_trans_read_buf(mp, tp, mp->m_ddev_targp, dqp->q_blkno,
				   mp->m_quotainfo->qi_dqchunklen,
				   0, bpp, NULL);

	if (error) {
		ASSERT(*bpp == NULL);
		return error;
	}
	(*bpp)->b_ops = &xfs_dquot_buf_ops;

	ASSERT(xfs_buf_islocked(*bpp));
	d = (struct xfs_dqblk *)(*bpp)->b_addr;


	for (i = 0; i < mp->m_quotainfo->qi_dqperchunk; i++) {
		ddq = &d[i].dd_diskdq;
		error = xfs_dqcheck(mp, ddq, firstid + i,
				       dqp->dq_flags & XFS_DQ_ALLTYPES,
				       XFS_QMOPT_DQREPAIR, "xfs_qm_dqrepair");
		if (error) {

			xfs_trans_brelse(tp, *bpp);
			return -EIO;
		}
	}

	return 0;
}
