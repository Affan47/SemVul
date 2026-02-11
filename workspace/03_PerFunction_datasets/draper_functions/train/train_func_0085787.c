trx_undo_get_first_rec(

	ulint	space,
	ulint	zip_size,

	ulint	page_no,
	ulint	offset,
	ulint	mode,
	mtr_t*	mtr)
{
	page_t*		undo_page;
	trx_undo_rec_t*	rec;

	if (mode == RW_S_LATCH) {
		undo_page = trx_undo_page_get_s_latched(space, zip_size,
							page_no, mtr);
	} else {
		undo_page = trx_undo_page_get(space, zip_size, page_no, mtr);
	}

	rec = trx_undo_page_get_first_rec(undo_page, page_no, offset);

	if (rec) {
		return(rec);
	}

	return(trx_undo_get_next_rec_from_next_page(space, zip_size,
						    undo_page, page_no, offset,
						    mode, mtr));
}
