xfs_iomap_eof_align_last_fsb(
	xfs_mount_t	*mp,
	xfs_inode_t	*ip,
	xfs_extlen_t	extsize,
	xfs_fileoff_t	*last_fsb)
{
	xfs_extlen_t	align = 0;
	int		eof, error;

	if (!XFS_IS_REALTIME_INODE(ip)) {


		if (mp->m_swidth && (mp->m_flags & XFS_MOUNT_SWALLOC))
			align = mp->m_swidth;
		else if (mp->m_dalign)
			align = mp->m_dalign;

		if (align && XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, align))
			align = 0;
	}


	if (extsize) {
		if (align)
			align = roundup_64(align, extsize);
		else
			align = extsize;
	}

	if (align) {
		xfs_fileoff_t	new_last_fsb = roundup_64(*last_fsb, align);
		error = xfs_bmap_eof(ip, new_last_fsb, XFS_DATA_FORK, &eof);
		if (error)
			return error;
		if (eof)
			*last_fsb = new_last_fsb;
	}
	return 0;
}
