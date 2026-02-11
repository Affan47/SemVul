lock_clust_rec_read_check_and_lock(

	ulint			flags,

	const buf_block_t*	block,
	const rec_t*		rec,


	dict_index_t*		index,
	const ulint*		offsets,
	enum lock_mode		mode,


	ulint			gap_mode,

	que_thr_t*		thr)
{
	enum db_err	err;
	ulint		heap_no;

	ut_ad(dict_index_is_clust(index));
	ut_ad(block->frame == page_align(rec));
	ut_ad(page_rec_is_user_rec(rec) || page_rec_is_supremum(rec));
	ut_ad(gap_mode == LOCK_ORDINARY || gap_mode == LOCK_GAP
	      || gap_mode == LOCK_REC_NOT_GAP);
	ut_ad(rec_offs_validate(rec, index, offsets));

	if (flags & BTR_NO_LOCKING_FLAG) {

		return(DB_SUCCESS);
	}

	heap_no = page_rec_get_heap_no(rec);

	lock_mutex_enter_kernel();

	ut_ad(mode != LOCK_X
	      || lock_table_has(thr_get_trx(thr), index->table, LOCK_IX));
	ut_ad(mode != LOCK_S
	      || lock_table_has(thr_get_trx(thr), index->table, LOCK_IS));

	if (UNIV_LIKELY(heap_no != PAGE_HEAP_NO_SUPREMUM)) {

		lock_rec_convert_impl_to_expl(block, rec, index, offsets);
	}

	err = lock_rec_lock(FALSE, mode | gap_mode,
			    block, heap_no, index, thr);

	lock_mutex_exit_kernel();

	ut_ad(lock_rec_queue_validate(block, rec, index, offsets));

	return(err);
}
