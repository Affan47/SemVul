trx_undo_parse_add_undo_rec(

	byte*	ptr,
	byte*	end_ptr,
	page_t*	page)
{
	ulint	len;
	byte*	rec;
	ulint	first_free;

	if (end_ptr < ptr + 2) {

		return(NULL);
	}

	len = mach_read_from_2(ptr);
	ptr += 2;

	if (end_ptr < ptr + len) {

		return(NULL);
	}

	if (page == NULL) {

		return(ptr + len);
	}

	first_free = mach_read_from_2(page + TRX_UNDO_PAGE_HDR
				      + TRX_UNDO_PAGE_FREE);
	rec = page + first_free;

	mach_write_to_2(rec, first_free + 4 + len);
	mach_write_to_2(rec + 2 + len, first_free);

	mach_write_to_2(page + TRX_UNDO_PAGE_HDR + TRX_UNDO_PAGE_FREE,
			first_free + 4 + len);
	ut_memcpy(rec + 2, ptr, len);

	return(ptr + len);
}
