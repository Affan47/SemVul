xdes_get_descriptor_with_space_hdr(

	fsp_header_t*	sp_header,

	ulint		space,
	ulint		offset,


	mtr_t*		mtr)
{
	ulint	limit;
	ulint	size;
	ulint	zip_size;
	ulint	descr_page_no;
	page_t*	descr_page;

	ut_ad(mtr_memo_contains(mtr, fil_space_get_latch(space, NULL),
				MTR_MEMO_X_LOCK));
	ut_ad(mtr_memo_contains_page(mtr, sp_header, MTR_MEMO_PAGE_X_FIX));
	ut_ad(page_offset(sp_header) == FSP_HEADER_OFFSET);

	limit = mach_read_from_4(sp_header + FSP_FREE_LIMIT);
	size  = mach_read_from_4(sp_header + FSP_SIZE);
	zip_size = dict_table_flags_to_zip_size(
		mach_read_from_4(sp_header + FSP_SPACE_FLAGS));

	if ((offset >= size) || (offset >= limit)) {
		return(NULL);
	}

	descr_page_no = xdes_calc_descriptor_page(zip_size, offset);

	if (descr_page_no == 0) {


		descr_page = page_align(sp_header);
	} else {
		buf_block_t*	block;

		block = buf_page_get(space, zip_size, descr_page_no,
				     RW_X_LATCH, mtr);
		buf_block_dbg_add_level(block, SYNC_FSP_PAGE);

		descr_page = buf_block_get_frame(block);
	}

	return(descr_page + XDES_ARR_OFFSET
	       + XDES_SIZE * xdes_calc_descriptor_index(zip_size, offset));
}
