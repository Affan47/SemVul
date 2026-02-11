xfs_dir3_free_get_buf(
	xfs_da_args_t		*args,
	xfs_dir2_db_t		fbno,
	struct xfs_buf		**bpp)
{
	struct xfs_trans	*tp = args->trans;
	struct xfs_inode	*dp = args->dp;
	struct xfs_mount	*mp = dp->i_mount;
	struct xfs_buf		*bp;
	int			error;
	struct xfs_dir3_icfree_hdr hdr;

	error = xfs_da_get_buf(tp, dp, xfs_dir2_db_to_da(args->geo, fbno),
				   -1, &bp, XFS_DATA_FORK);
	if (error)
		return error;

	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DIR_FREE_BUF);
	bp->b_ops = &xfs_dir3_free_buf_ops;


	memset(bp->b_addr, 0, sizeof(struct xfs_dir3_free_hdr));
	memset(&hdr, 0, sizeof(hdr));

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_dir3_free_hdr *hdr3 = bp->b_addr;

		hdr.magic = XFS_DIR3_FREE_MAGIC;

		hdr3->hdr.blkno = cpu_to_be64(bp->b_bn);
		hdr3->hdr.owner = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdr3->hdr.uuid, &mp->m_sb.sb_meta_uuid);
	} else
		hdr.magic = XFS_DIR2_FREE_MAGIC;
	dp->d_ops->free_hdr_to_disk(bp->b_addr, &hdr);
	*bpp = bp;
	return 0;
}
