lock_rec_free_all_from_discard_page(

	const buf_block_t*	block)
{
	ulint	space;
	ulint	page_no;
	lock_t*	lock;
	lock_t*	next_lock;

	ut_ad(mutex_own(&kernel_mutex));

	space = buf_block_get_space(block);
	page_no = buf_block_get_page_no(block);

	lock = lock_rec_get_first_on_page_addr(space, page_no);

	while (lock != NULL) {
		ut_ad(lock_rec_find_set_bit(lock) == ULINT_UNDEFINED);
		ut_ad(!lock_get_wait(lock));

		next_lock = lock_rec_get_next_on_page(lock);

		lock_rec_discard(lock);

		lock = next_lock;
	}
}
