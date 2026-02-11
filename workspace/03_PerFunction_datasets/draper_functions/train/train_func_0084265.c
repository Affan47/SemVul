xfs_alloc_read_agf(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	int			flags,
	struct xfs_buf		**bpp)
{
	struct xfs_agf		*agf;
	struct xfs_perag	*pag;
	int			error;

	trace_xfs_alloc_read_agf(mp, agno);

	ASSERT(agno != NULLAGNUMBER);
	error = xfs_read_agf(mp, tp, agno,
			(flags & XFS_ALLOC_FLAG_TRYLOCK) ? XBF_TRYLOCK : 0,
			bpp);
	if (error)
		return error;
	if (!*bpp)
		return 0;
	ASSERT(!(*bpp)->b_error);

	agf = XFS_BUF_TO_AGF(*bpp);
	pag = xfs_perag_get(mp, agno);
	if (!pag->pagf_init) {
		pag->pagf_freeblks = be32_to_cpu(agf->agf_freeblks);
		pag->pagf_btreeblks = be32_to_cpu(agf->agf_btreeblks);
		pag->pagf_flcount = be32_to_cpu(agf->agf_flcount);
		pag->pagf_longest = be32_to_cpu(agf->agf_longest);
		pag->pagf_levels[XFS_BTNUM_BNOi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNOi]);
		pag->pagf_levels[XFS_BTNUM_CNTi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNTi]);
		spin_lock_init(&pag->pagb_lock);
		pag->pagb_count = 0;
		pag->pagb_tree = RB_ROOT;
		pag->pagf_init = 1;
	}
#ifdef DEBUG
	else if (!XFS_FORCED_SHUTDOWN(mp)) {
		ASSERT(pag->pagf_freeblks == be32_to_cpu(agf->agf_freeblks));
		ASSERT(pag->pagf_btreeblks == be32_to_cpu(agf->agf_btreeblks));
		ASSERT(pag->pagf_flcount == be32_to_cpu(agf->agf_flcount));
		ASSERT(pag->pagf_longest == be32_to_cpu(agf->agf_longest));
		ASSERT(pag->pagf_levels[XFS_BTNUM_BNOi] ==
		       be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNOi]));
		ASSERT(pag->pagf_levels[XFS_BTNUM_CNTi] ==
		       be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNTi]));
	}
#endif
	xfs_perag_put(pag);
	return 0;
}
