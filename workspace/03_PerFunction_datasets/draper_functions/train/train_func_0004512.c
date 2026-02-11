xlog_recover_check_summary(
	struct xlog	*log)
{
	xfs_mount_t	*mp;
	xfs_agf_t	*agfp;
	xfs_buf_t	*agfbp;
	xfs_buf_t	*agibp;
	xfs_agnumber_t	agno;
	__uint64_t	freeblks;
	__uint64_t	itotal;
	__uint64_t	ifree;
	int		error;

	mp = log->l_mp;

	freeblks = 0LL;
	itotal = 0LL;
	ifree = 0LL;
	for (agno = 0; agno < mp->m_sb.sb_agcount; agno++) {
		error = xfs_read_agf(mp, NULL, agno, 0, &agfbp);
		if (error) {
			xfs_alert(mp, "%s agf read failed agno %d error %d",
						__func__, agno, error);
		} else {
			agfp = XFS_BUF_TO_AGF(agfbp);
			freeblks += be32_to_cpu(agfp->agf_freeblks) +
				    be32_to_cpu(agfp->agf_flcount);
			xfs_buf_relse(agfbp);
		}

		error = xfs_read_agi(mp, NULL, agno, &agibp);
		if (error) {
			xfs_alert(mp, "%s agi read failed agno %d error %d",
						__func__, agno, error);
		} else {
			struct xfs_agi	*agi = XFS_BUF_TO_AGI(agibp);

			itotal += be32_to_cpu(agi->agi_count);
			ifree += be32_to_cpu(agi->agi_freecount);
			xfs_buf_relse(agibp);
		}
	}
}
