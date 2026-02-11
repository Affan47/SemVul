ibuf_bitmap_page_init(

	buf_block_t*	block,
	mtr_t*		mtr)
{
	page_t*	page;
	ulint	byte_offset;
	ulint	zip_size = buf_block_get_zip_size(block);

	ut_a(ut_is_2pow(zip_size));

	page = buf_block_get_frame(block);
	fil_page_set_type(page, FIL_PAGE_IBUF_BITMAP);


	if (!zip_size) {
		byte_offset = UT_BITS_IN_BYTES(UNIV_PAGE_SIZE
					       * IBUF_BITS_PER_PAGE);
	} else {
		byte_offset = UT_BITS_IN_BYTES(zip_size * IBUF_BITS_PER_PAGE);
	}

	memset(page + IBUF_BITMAP, 0, byte_offset);


#ifndef UNIV_HOTBACKUP
	mlog_write_initial_log_record(page, MLOG_IBUF_BITMAP_INIT, mtr);
#endif
}
