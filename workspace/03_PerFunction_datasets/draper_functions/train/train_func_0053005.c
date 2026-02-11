xfs_iext_irec_compact_pages(
	xfs_ifork_t	*ifp)
{
	xfs_ext_irec_t	*erp, *erp_next;
	int		erp_idx = 0;
	int		nlists;

	ASSERT(ifp->if_flags & XFS_IFEXTIREC);
	nlists = ifp->if_real_bytes / XFS_IEXT_BUFSZ;
	while (erp_idx < nlists - 1) {
		erp = &ifp->if_u1.if_ext_irec[erp_idx];
		erp_next = erp + 1;
		if (erp_next->er_extcount <=
		    (XFS_LINEAR_EXTS - erp->er_extcount)) {
			memcpy(&erp->er_extbuf[erp->er_extcount],
				erp_next->er_extbuf, erp_next->er_extcount *
				sizeof(xfs_bmbt_rec_t));
			erp->er_extcount += erp_next->er_extcount;


			kmem_free(erp_next->er_extbuf);
			erp_next->er_extbuf = NULL;
			xfs_iext_irec_remove(ifp, erp_idx + 1);
			nlists = ifp->if_real_bytes / XFS_IEXT_BUFSZ;
		} else {
			erp_idx++;
		}
	}
}
