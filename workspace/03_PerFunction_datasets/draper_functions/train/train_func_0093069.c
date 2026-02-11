row_ins_duplicate_error_in_clust(

	btr_cur_t*	cursor,
	const dtuple_t*	entry,
	que_thr_t*	thr,
	mtr_t*		mtr)
{
	ulint	err;
	rec_t*	rec;
	ulint	n_unique;
	trx_t*	trx		= thr_get_trx(thr);
	mem_heap_t*heap		= NULL;
	ulint	offsets_[REC_OFFS_NORMAL_SIZE];
	ulint*	offsets		= offsets_;
	rec_offs_init(offsets_);

	UT_NOT_USED(mtr);

	ut_a(dict_index_is_clust(cursor->index));
	ut_ad(dict_index_is_unique(cursor->index));


	n_unique = dict_index_get_n_unique(cursor->index);

	if (cursor->low_match >= n_unique) {

		rec = btr_cur_get_rec(cursor);

		if (!page_rec_is_infimum(rec)) {
			offsets = rec_get_offsets(rec, cursor->index, offsets,
						  ULINT_UNDEFINED, &heap);


			if (trx->duplicates) {


				err = row_ins_set_exclusive_rec_lock(
					LOCK_REC_NOT_GAP,
					btr_cur_get_block(cursor),
					rec, cursor->index, offsets, thr);
			} else {

				err = row_ins_set_shared_rec_lock(
					LOCK_REC_NOT_GAP,
					btr_cur_get_block(cursor), rec,
					cursor->index, offsets, thr);
			}

			switch (err) {
			case DB_SUCCESS_LOCKED_REC:
			case DB_SUCCESS:
				break;
			default:
				goto func_exit;
			}

			if (row_ins_dupl_error_with_rec(
				    rec, entry, cursor->index, offsets)) {
				trx->error_info = cursor->index;
				err = DB_DUPLICATE_KEY;
				goto func_exit;
			}
		}
	}

	if (cursor->up_match >= n_unique) {

		rec = page_rec_get_next(btr_cur_get_rec(cursor));

		if (!page_rec_is_supremum(rec)) {
			offsets = rec_get_offsets(rec, cursor->index, offsets,
						  ULINT_UNDEFINED, &heap);

			if (trx->duplicates) {


				err = row_ins_set_exclusive_rec_lock(
					LOCK_REC_NOT_GAP,
					btr_cur_get_block(cursor),
					rec, cursor->index, offsets, thr);
			} else {

				err = row_ins_set_shared_rec_lock(
					LOCK_REC_NOT_GAP,
					btr_cur_get_block(cursor),
					rec, cursor->index, offsets, thr);
			}

			switch (err) {
			case DB_SUCCESS_LOCKED_REC:
			case DB_SUCCESS:
				break;
			default:
				goto func_exit;
			}

			if (row_ins_dupl_error_with_rec(
				    rec, entry, cursor->index, offsets)) {
				trx->error_info = cursor->index;
				err = DB_DUPLICATE_KEY;
				goto func_exit;
			}
		}

		ut_a(!dict_index_is_clust(cursor->index));

	}

	err = DB_SUCCESS;
func_exit:
	if (UNIV_LIKELY_NULL(heap)) {
		mem_heap_free(heap);
	}
	return(err);
}
