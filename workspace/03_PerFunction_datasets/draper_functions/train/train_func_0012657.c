trx_purge_truncate_rseg_history(

	trx_rseg_t*	rseg,
	trx_id_t	limit_trx_no,

	undo_no_t	limit_undo_no)


{
	fil_addr_t	hdr_addr;
	fil_addr_t	prev_hdr_addr;
	trx_rsegf_t*	rseg_hdr;
	page_t*		undo_page;
	trx_ulogf_t*	log_hdr;
	trx_usegf_t*	seg_hdr;
	ulint		n_removed_logs	= 0;
	mtr_t		mtr;
	trx_id_t	undo_trx_no;

	mtr_start(&mtr);
	mutex_enter(&(rseg->mutex));

	rseg_hdr = trx_rsegf_get(rseg->space, rseg->zip_size,
				 rseg->page_no, &mtr);

	hdr_addr = trx_purge_get_log_from_hist(
		flst_get_last(rseg_hdr + TRX_RSEG_HISTORY, &mtr));
loop:
	if (hdr_addr.page == FIL_NULL) {

		mutex_exit(&(rseg->mutex));

		mtr_commit(&mtr);

		return;
	}

	undo_page = trx_undo_page_get(rseg->space, rseg->zip_size,
				      hdr_addr.page, &mtr);

	log_hdr = undo_page + hdr_addr.boffset;
	undo_trx_no = mach_read_from_8(log_hdr + TRX_UNDO_TRX_NO);

	if (undo_trx_no >= limit_trx_no) {
		if (undo_trx_no == limit_trx_no) {
			trx_undo_truncate_start(rseg, rseg->space,
						hdr_addr.page,
						hdr_addr.boffset,
						limit_undo_no);
		}

		mutex_enter(&kernel_mutex);
		ut_a(trx_sys->rseg_history_len >= n_removed_logs);
		trx_sys->rseg_history_len -= n_removed_logs;
		mutex_exit(&kernel_mutex);

		flst_truncate_end(rseg_hdr + TRX_RSEG_HISTORY,
				  log_hdr + TRX_UNDO_HISTORY_NODE,
				  n_removed_logs, &mtr);

		mutex_exit(&(rseg->mutex));
		mtr_commit(&mtr);

		return;
	}

	prev_hdr_addr = trx_purge_get_log_from_hist(
		flst_get_prev_addr(log_hdr + TRX_UNDO_HISTORY_NODE, &mtr));
	n_removed_logs++;

	seg_hdr = undo_page + TRX_UNDO_SEG_HDR;

	if ((mach_read_from_2(seg_hdr + TRX_UNDO_STATE) == TRX_UNDO_TO_PURGE)
	    && (mach_read_from_2(log_hdr + TRX_UNDO_NEXT_LOG) == 0)) {


		mutex_exit(&(rseg->mutex));
		mtr_commit(&mtr);

		trx_purge_free_segment(rseg, hdr_addr, n_removed_logs);

		n_removed_logs = 0;
	} else {
		mutex_exit(&(rseg->mutex));
		mtr_commit(&mtr);
	}

	mtr_start(&mtr);
	mutex_enter(&(rseg->mutex));

	rseg_hdr = trx_rsegf_get(rseg->space, rseg->zip_size,
				 rseg->page_no, &mtr);

	hdr_addr = prev_hdr_addr;

	goto loop;
}
