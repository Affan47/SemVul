xfs_iomap_eof_prealloc_initial_size(
	struct xfs_mount	*mp,
	struct xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_bmbt_irec_t		*imap,
	int			nimaps)
{
	xfs_fileoff_t   start_fsb;
	int		imaps = 1;
	int		error;

	ASSERT(nimaps >= imaps);


	if (mp->m_flags & XFS_MOUNT_DFLT_IOSIZE)
		return 0;


	if (XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, mp->m_dalign))
		return 0;


	start_fsb = XFS_B_TO_FSB(mp, offset);
	if (start_fsb)
		start_fsb--;
	error = xfs_bmapi_read(ip, start_fsb, 1, imap, &imaps, XFS_BMAPI_ENTIRE);
	if (error)
		return 0;

	ASSERT(imaps == 1);
	if (imap[0].br_startblock == HOLESTARTBLOCK)
		return 0;
	if (imap[0].br_blockcount <= (MAXEXTLEN >> 1))
		return imap[0].br_blockcount << 1;
	return XFS_B_TO_FSB(mp, offset);
}
