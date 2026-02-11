xfs_iext_irec_compact(
	xfs_ifork_t	*ifp)
{
	xfs_extnum_t	nextents;
	int		nlists;

	ASSERT(ifp->if_flags & XFS_IFEXTIREC);
	nlists = ifp->if_real_bytes / XFS_IEXT_BUFSZ;
	nextents = ifp->if_bytes / (uint)sizeof(xfs_bmbt_rec_t);

	if (nextents == 0) {
		xfs_iext_destroy(ifp);
	} else if (nextents <= XFS_INLINE_EXTS) {
		xfs_iext_indirect_to_direct(ifp);
		xfs_iext_direct_to_inline(ifp, nextents);
	} else if (nextents <= XFS_LINEAR_EXTS) {
		xfs_iext_indirect_to_direct(ifp);
	} else if (nextents < (nlists * XFS_LINEAR_EXTS) >> 1) {
		xfs_iext_irec_compact_pages(ifp);
	}
}
