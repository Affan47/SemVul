mtr_memo_pop_all(

	mtr_t*	mtr)
{
	const dyn_block_t*	block;

	ut_ad(mtr->magic_n == MTR_MAGIC_N);
	ut_ad(mtr->state == MTR_COMMITTING);


	for (block = dyn_array_get_last_block(&mtr->memo);
	     block;
	     block = dyn_array_get_prev_block(&mtr->memo, block)) {
		const mtr_memo_slot_t*	start
			= (mtr_memo_slot_t*) dyn_block_get_data(block);
		mtr_memo_slot_t*	slot
			= (mtr_memo_slot_t*) (dyn_block_get_data(block)
					      + dyn_block_get_used(block));

		ut_ad(!(dyn_block_get_used(block) % sizeof(mtr_memo_slot_t)));

		while (slot-- != start) {
			if (slot->object != NULL) {
				mtr_memo_slot_release(mtr, slot);
			}
		}
	}
}
