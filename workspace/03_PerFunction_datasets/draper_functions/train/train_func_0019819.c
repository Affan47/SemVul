fseg_alloc_free_extent(

	fseg_inode_t*	inode,
	ulint		space,
	ulint		zip_size,

	mtr_t*		mtr)
{
	xdes_t*		descr;
	ib_id_t		seg_id;
	fil_addr_t	first;

	ut_ad(!((page_offset(inode) - FSEG_ARR_OFFSET) % FSEG_INODE_SIZE));
	ut_ad(mach_read_from_4(inode + FSEG_MAGIC_N) == FSEG_MAGIC_N_VALUE);

	if (flst_get_len(inode + FSEG_FREE, mtr) > 0) {


		first = flst_get_first(inode + FSEG_FREE, mtr);

		descr = xdes_lst_get_descriptor(space, zip_size, first, mtr);
	} else {

		descr = fsp_alloc_free_extent(space, zip_size, 0, mtr);

		if (descr == NULL) {

			return(NULL);
		}

		seg_id = mach_read_from_8(inode + FSEG_ID);

		xdes_set_state(descr, XDES_FSEG, mtr);
		mlog_write_ull(descr + XDES_ID, seg_id, mtr);
		flst_add_last(inode + FSEG_FREE, descr + XDES_FLST_NODE, mtr);


		fseg_fill_free_list(inode, space, zip_size,
				    xdes_get_offset(descr) + FSP_EXTENT_SIZE,
				    mtr);
	}

	return(descr);
}
