xfs_dir2_block_lookup(
	xfs_da_args_t		*args)
{
	xfs_dir2_data_hdr_t	*hdr;
	xfs_dir2_leaf_entry_t	*blp;
	struct xfs_buf		*bp;
	xfs_dir2_block_tail_t	*btp;
	xfs_dir2_data_entry_t	*dep;
	xfs_inode_t		*dp;
	int			ent;
	int			error;

	trace_xfs_dir2_block_lookup(args);


	if ((error = xfs_dir2_block_lookup_int(args, &bp, &ent)))
		return error;
	dp = args->dp;
	hdr = bp->b_addr;
	xfs_dir3_data_check(dp, bp);
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);


	dep = (xfs_dir2_data_entry_t *)((char *)hdr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(blp[ent].address)));


	args->inumber = be64_to_cpu(dep->inumber);
	args->filetype = dp->d_ops->data_get_ftype(dep);
	error = xfs_dir_cilookup_result(args, dep->name, dep->namelen);
	xfs_trans_brelse(args->trans, bp);
	return error;
}
