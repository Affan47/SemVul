trx_undo_truncate_end_func(

#ifdef UNIV_DEBUG
	const trx_t*	trx,
#endif
	trx_undo_t*	undo,
	undo_no_t	limit)

{
	page_t*		undo_page;
	ulint		last_page_no;
	trx_undo_rec_t* rec;
	trx_undo_rec_t* trunc_here;
	mtr_t		mtr;

	ut_ad(mutex_own(&(trx->undo_mutex)));
	ut_ad(mutex_own(&(trx->rseg->mutex)));

	for (;;) {
		mtr_start(&mtr);

		trunc_here = NULL;

		last_page_no = undo->last_page_no;

		undo_page = trx_undo_page_get(undo->space, undo->zip_size,
					      last_page_no, &mtr);

		rec = trx_undo_page_get_last_rec(undo_page, undo->hdr_page_no,
						 undo->hdr_offset);
		while (rec) {
			if (trx_undo_rec_get_undo_no(rec) >= limit) {


				trunc_here = rec;
			} else {
				goto function_exit;
			}

			rec = trx_undo_page_get_prev_rec(rec,
							 undo->hdr_page_no,
							 undo->hdr_offset);
		}

		if (last_page_no == undo->hdr_page_no) {

			goto function_exit;
		}

		ut_ad(last_page_no == undo->last_page_no);
		trx_undo_free_last_page(trx, undo, &mtr);

		mtr_commit(&mtr);
	}

function_exit:
	if (trunc_here) {
		mlog_write_ulint(undo_page + TRX_UNDO_PAGE_HDR
				 + TRX_UNDO_PAGE_FREE,
				 trunc_here - undo_page, MLOG_2BYTES, &mtr);
	}

	mtr_commit(&mtr);
}
