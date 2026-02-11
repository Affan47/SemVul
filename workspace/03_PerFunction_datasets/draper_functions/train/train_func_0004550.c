xfs_ialloc_compute_maxlevels(
	xfs_mount_t	*mp)
{
	int		level;
	uint		maxblocks;
	uint		maxleafents;
	int		minleafrecs;
	int		minnoderecs;

	maxleafents = (1LL << XFS_INO_AGINO_BITS(mp)) >>
		XFS_INODES_PER_CHUNK_LOG;
	minleafrecs = mp->m_alloc_mnr[0];
	minnoderecs = mp->m_alloc_mnr[1];
	maxblocks = (maxleafents + minleafrecs - 1) / minleafrecs;
	for (level = 1; maxblocks > 1; level++)
		maxblocks = (maxblocks + minnoderecs - 1) / minnoderecs;
	mp->m_in_maxlevels = level;
}
