lock_rec_convert_impl_to_expl(

	const buf_block_t*	block,
	const rec_t*		rec,
	dict_index_t*		index,
	const ulint*		offsets)
{
	trx_t*	impl_trx;

	ut_ad(mutex_own(&kernel_mutex));
	ut_ad(page_rec_is_user_rec(rec));
	ut_ad(rec_offs_validate(rec, index, offsets));
	ut_ad(!page_rec_is_comp(rec) == !rec_offs_comp(offsets));

	if (dict_index_is_clust(index)) {
		impl_trx = lock_clust_rec_some_has_impl(rec, index, offsets);
	} else {
		impl_trx = lock_sec_rec_some_has_impl_off_kernel(
			rec, index, offsets);
	}

	if (impl_trx) {
		ulint	heap_no = page_rec_get_heap_no(rec);


		if (!lock_rec_has_expl(LOCK_X | LOCK_REC_NOT_GAP, block,
				       heap_no, impl_trx)) {
			ulint	type_mode = (LOCK_REC | LOCK_X
					     | LOCK_REC_NOT_GAP);


			if (rec_get_deleted_flag(rec, rec_offs_comp(offsets))
			    && lock_rec_other_has_conflicting(
					LOCK_X | LOCK_REC_NOT_GAP, block,
					heap_no, impl_trx)) {

				type_mode |= (LOCK_WAIT | LOCK_CONV_BY_OTHER);
			}

			lock_rec_add_to_queue(
				type_mode, block, heap_no, index, impl_trx);
		}
	}
}
