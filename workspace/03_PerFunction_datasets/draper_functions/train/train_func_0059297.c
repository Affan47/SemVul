xfs_rtfree_range(
	xfs_mount_t	*mp,
	xfs_trans_t	*tp,
	xfs_rtblock_t	start,
	xfs_extlen_t	len,
	xfs_buf_t	**rbpp,
	xfs_fsblock_t	*rsb)
{
	xfs_rtblock_t	end;
	int		error;
	xfs_rtblock_t	postblock;
	xfs_rtblock_t	preblock;

	end = start + len - 1;


	error = xfs_rtmodify_range(mp, tp, start, len, 1);
	if (error) {
		return error;
	}


	error = xfs_rtfind_back(mp, tp, start, 0, &preblock);
	if (error) {
		return error;
	}


	error = xfs_rtfind_forw(mp, tp, end, mp->m_sb.sb_rextents - 1,
		&postblock);
	if (error)
		return error;


	if (preblock < start) {
		error = xfs_rtmodify_summary(mp, tp,
			XFS_RTBLOCKLOG(start - preblock),
			XFS_BITTOBLOCK(mp, preblock), -1, rbpp, rsb);
		if (error) {
			return error;
		}
	}


	if (postblock > end) {
		error = xfs_rtmodify_summary(mp, tp,
			XFS_RTBLOCKLOG(postblock - end),
			XFS_BITTOBLOCK(mp, end + 1), -1, rbpp, rsb);
		if (error) {
			return error;
		}
	}


	error = xfs_rtmodify_summary(mp, tp,
		XFS_RTBLOCKLOG(postblock + 1 - preblock),
		XFS_BITTOBLOCK(mp, preblock), 1, rbpp, rsb);
	return error;
}
