rw_lock_free_func(

	rw_lock_t*	lock)
{
	ut_ad(rw_lock_validate(lock));
	ut_a(lock->lock_word == X_LOCK_DECR);

#ifndef INNODB_RW_LOCKS_USE_ATOMICS
	mutex_free(rw_lock_get_mutex(lock));
#endif

	mutex_enter(&rw_lock_list_mutex);
	os_event_free(lock->event);

	os_event_free(lock->wait_ex_event);

	ut_ad(UT_LIST_GET_PREV(list, lock) == NULL
	      || UT_LIST_GET_PREV(list, lock)->magic_n == RW_LOCK_MAGIC_N);
	ut_ad(UT_LIST_GET_NEXT(list, lock) == NULL
	      || UT_LIST_GET_NEXT(list, lock)->magic_n == RW_LOCK_MAGIC_N);

	UT_LIST_REMOVE(list, rw_lock_list, lock);

	mutex_exit(&rw_lock_list_mutex);

	ut_d(lock->magic_n = 0);
}
