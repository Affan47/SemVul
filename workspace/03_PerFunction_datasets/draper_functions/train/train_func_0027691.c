get_inorecptr(int is_aggregate,
		  int alloc,
		  uint32_t inonum, struct fsck_inode_record **addr_inorecptr)
{
	int gir_rc = FSCK_OK;

	if (is_aggregate) {

		if (alloc) {

			gir_rc =
			    inorec_agg_search_insert(inonum, addr_inorecptr);
		} else {

			gir_rc = inorec_agg_search(inonum, addr_inorecptr);
		}
	} else {

		if (alloc) {

			gir_rc =
			    inorec_fs_search_insert(inonum, addr_inorecptr);
		} else {

			gir_rc = inorec_fs_search(inonum, addr_inorecptr);
		}
	}

	return (gir_rc);
}
