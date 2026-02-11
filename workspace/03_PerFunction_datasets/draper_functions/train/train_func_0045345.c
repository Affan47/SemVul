xfs_dir3_data_block_free(
	xfs_da_args_t		*args,
	struct xfs_dir2_data_hdr *hdr,
	struct xfs_dir2_free	*free,
	xfs_dir2_db_t		fdb,
	int			findex,
	struct xfs_buf		*fbp,
	int			longest)
{
	int			logfree = 0;
	__be16			*bests;
	struct xfs_dir3_icfree_hdr freehdr;
	struct xfs_inode	*dp = args->dp;

	dp->d_ops->free_hdr_from_disk(&freehdr, free);
	bests = dp->d_ops->free_bests_p(free);
	if (hdr) {


		bests[findex] = cpu_to_be16(longest);
		xfs_dir2_free_log_bests(args, fbp, findex, findex);
		return 0;
	}


	freehdr.nused--;


	if (findex == freehdr.nvalid - 1) {
		int	i;

		for (i = findex - 1; i >= 0; i--) {
			if (bests[i] != cpu_to_be16(NULLDATAOFF))
				break;
		}
		freehdr.nvalid = i + 1;
		logfree = 0;
	} else {

		bests[findex] = cpu_to_be16(NULLDATAOFF);
		logfree = 1;
	}

	dp->d_ops->free_hdr_to_disk(free, &freehdr);
	xfs_dir2_free_log_header(args, fbp);


	if (!freehdr.nused) {
		int error;

		error = xfs_dir2_shrink_inode(args, fdb, fbp);
		if (error == 0) {
			fbp = NULL;
			logfree = 0;
		} else if (error != -ENOSPC || args->total != 0)
			return error;


	}


	if (logfree)
		xfs_dir2_free_log_bests(args, fbp, findex, findex);
	return 0;
}
