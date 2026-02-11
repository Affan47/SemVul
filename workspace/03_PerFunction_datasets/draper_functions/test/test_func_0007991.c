xfs_dir2_isblock(
	struct xfs_da_args	*args,
	int			*vp)
{
	xfs_fileoff_t		last;
	int			rval;

	if ((rval = xfs_bmap_last_offset(args->dp, &last, XFS_DATA_FORK)))
		return rval;
	rval = XFS_FSB_TO_B(args->dp->i_mount, last) == args->geo->blksize;
	ASSERT(rval == 0 || args->dp->i_d.di_size == args->geo->blksize);
	*vp = rval;
	return 0;
}
