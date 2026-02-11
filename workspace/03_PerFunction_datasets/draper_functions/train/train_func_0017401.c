pnfs_layout_need_return(struct pnfs_layout_hdr *lo,
			struct pnfs_layout_segment *lseg)
{
	struct pnfs_layout_segment *s;

	if (!test_and_clear_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags))
		return false;

	list_for_each_entry(s, &lo->plh_segs, pls_list)
		if (s != lseg && test_bit(NFS_LSEG_LAYOUTRETURN, &s->pls_flags))
			return false;

	return true;
}
