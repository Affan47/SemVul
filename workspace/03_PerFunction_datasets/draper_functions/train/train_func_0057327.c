trx_lock_wait_to_suspended(

	trx_t*	trx)
{
	que_thr_t*	thr;

	ut_ad(mutex_own(&kernel_mutex));
	ut_ad(trx->que_state == TRX_QUE_LOCK_WAIT);

	thr = UT_LIST_GET_FIRST(trx->wait_thrs);

	while (thr != NULL) {
		thr->state = QUE_THR_SUSPENDED;

		UT_LIST_REMOVE(trx_thrs, trx->wait_thrs, thr);

		thr = UT_LIST_GET_FIRST(trx->wait_thrs);
	}

	trx->que_state = TRX_QUE_RUNNING;
}
