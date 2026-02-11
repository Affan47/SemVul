lock_cancel_waiting_and_release(

	lock_t*	lock)
{
	ut_ad(mutex_own(&kernel_mutex));
	ut_ad(!(lock->type_mode & LOCK_CONV_BY_OTHER));

	if (lock_get_type_low(lock) == LOCK_REC) {

		lock_rec_dequeue_from_page(lock);
	} else {
		ut_ad(lock_get_type_low(lock) & LOCK_TABLE);

		if (lock->trx->autoinc_locks != NULL) {

			lock_release_autoinc_locks(lock->trx);
		}

		lock_table_dequeue(lock);
	}


	lock_reset_lock_and_trx_wait(lock);


	trx_end_lock_wait(lock->trx);
}
