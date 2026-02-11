xfs_rtpick_extent(
	xfs_mount_t	*mp,
	xfs_trans_t	*tp,
	xfs_extlen_t	len,
	xfs_rtblock_t	*pick)
{
	xfs_rtblock_t	b;
	int		log2;
	__uint64_t	resid;
	__uint64_t	seq;
	__uint64_t	*seqp;

	ASSERT(xfs_isilocked(mp->m_rbmip, XFS_ILOCK_EXCL));

	seqp = (__uint64_t *)&mp->m_rbmip->i_d.di_atime;
	if (!(mp->m_rbmip->i_d.di_flags & XFS_DIFLAG_NEWRTBM)) {
		mp->m_rbmip->i_d.di_flags |= XFS_DIFLAG_NEWRTBM;
		*seqp = 0;
	}
	seq = *seqp;
	if ((log2 = xfs_highbit64(seq)) == -1)
		b = 0;
	else {
		resid = seq - (1ULL << log2);
		b = (mp->m_sb.sb_rextents * ((resid << 1) + 1ULL)) >>
		    (log2 + 1);
		if (b >= mp->m_sb.sb_rextents)
			b = do_mod(b, mp->m_sb.sb_rextents);
		if (b + len > mp->m_sb.sb_rextents)
			b = mp->m_sb.sb_rextents - len;
	}
	*seqp = seq + 1;
	xfs_trans_log_inode(tp, mp->m_rbmip, XFS_ILOG_CORE);
	*pick = b;
	return 0;
}
