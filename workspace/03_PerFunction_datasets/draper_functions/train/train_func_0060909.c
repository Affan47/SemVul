lock_rec_lock_fast(

	ibool			impl,


	ulint			mode,


	const buf_block_t*	block,

	ulint			heap_no,
	dict_index_t*		index,
	que_thr_t*		thr)
{
	lock_t*	lock;
	trx_t*	trx;

	ut_ad(mutex_own(&kernel_mutex));
	ut_ad((LOCK_MODE_MASK & mode) != LOCK_S
	      || lock_table_has(thr_get_trx(thr), index->table, LOCK_IS));
	ut_ad((LOCK_MODE_MASK & mode) != LOCK_X
	      || lock_table_has(thr_get_trx(thr), index->table, LOCK_IX));
	ut_ad((LOCK_MODE_MASK & mode) == LOCK_S
	      || (LOCK_MODE_MASK & mode) == LOCK_X);
	ut_ad(mode - (LOCK_MODE_MASK & mode) == LOCK_GAP
	      || mode - (LOCK_MODE_MASK & mode) == 0
	      || mode - (LOCK_MODE_MASK & mode) == LOCK_REC_NOT_GAP);

	DBUG_EXECUTE_IF("innodb_report_deadlock", return(LOCK_REC_FAIL););

	lock = lock_rec_get_first_on_page(block);

	trx = thr_get_trx(thr);

	if (lock == NULL) {
		if (!impl) {
			lock_rec_create(mode, block, heap_no, index, trx);
		}

		return(LOCK_REC_SUCCESS_CREATED);
	}

	if (lock_rec_get_next_on_page(lock)) {

		return(LOCK_REC_FAIL);
	}

	if (lock->trx != trx
	    || lock->type_mode != (mode | LOCK_REC)
	    || lock_rec_get_n_bits(lock) <= heap_no) {

		return(LOCK_REC_FAIL);
	}

	if (!impl) {


		if (!lock_rec_get_nth_bit(lock, heap_no)) {
			lock_rec_set_nth_bit(lock, heap_no);
			return(LOCK_REC_SUCCESS_CREATED);
		}
	}

	return(LOCK_REC_SUCCESS);
}
