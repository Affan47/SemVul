xfs_dialloc_ag_finobt_newino(
	struct xfs_agi			*agi,
	struct xfs_btree_cur		*cur,
	struct xfs_inobt_rec_incore	*rec)
{
	int error;
	int i;

	if (agi->agi_newino != cpu_to_be32(NULLAGINO)) {
		error = xfs_inobt_lookup(cur, be32_to_cpu(agi->agi_newino),
					 XFS_LOOKUP_EQ, &i);
		if (error)
			return error;
		if (i == 1) {
			error = xfs_inobt_get_rec(cur, rec, &i);
			if (error)
				return error;
			XFS_WANT_CORRUPTED_RETURN(cur->bc_mp, i == 1);
			return 0;
		}
	}


	error = xfs_inobt_lookup(cur, 0, XFS_LOOKUP_GE, &i);
	if (error)
		return error;
	XFS_WANT_CORRUPTED_RETURN(cur->bc_mp, i == 1);

	error = xfs_inobt_get_rec(cur, rec, &i);
	if (error)
		return error;
	XFS_WANT_CORRUPTED_RETURN(cur->bc_mp, i == 1);

	return 0;
}
