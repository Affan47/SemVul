xfs_dir2_shrink_inode(
	xfs_da_args_t	*args,
	xfs_dir2_db_t	db,
	struct xfs_buf	*bp)
{
	xfs_fileoff_t	bno;
	xfs_dablk_t	da;
	int		done;
	xfs_inode_t	*dp;
	int		error;
	xfs_mount_t	*mp;
	xfs_trans_t	*tp;

	trace_xfs_dir2_shrink_inode(args, db);

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	da = xfs_dir2_db_to_da(args->geo, db);


	error = xfs_bunmapi(tp, dp, da, args->geo->fsbcount, 0, 0,
			    args->firstblock, args->flist, &done);
	if (error) {


		return error;
	}
	ASSERT(done);


	xfs_trans_binval(tp, bp);


	if (db >= xfs_dir2_byte_to_db(args->geo, XFS_DIR2_LEAF_OFFSET))
		return 0;


	if (dp->i_d.di_size > xfs_dir2_db_off_to_byte(args->geo, db + 1, 0))
		return 0;
	bno = da;
	if ((error = xfs_bmap_last_before(tp, dp, &bno, XFS_DATA_FORK))) {


		return error;
	}
	if (db == args->geo->datablk)
		ASSERT(bno == 0);
	else
		ASSERT(bno > 0);


	dp->i_d.di_size = XFS_FSB_TO_B(mp, bno);
	xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);
	return 0;
}
