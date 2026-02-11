trx_handle_commit_sig_off_kernel(

	trx_t*		trx,
	que_thr_t**	next_thr)


{
	trx_sig_t*	sig;
	trx_sig_t*	next_sig;

	ut_ad(mutex_own(&kernel_mutex));

	trx->que_state = TRX_QUE_COMMITTING;

	trx_commit_off_kernel(trx);

	ut_ad(UT_LIST_GET_LEN(trx->wait_thrs) == 0);


	sig = UT_LIST_GET_FIRST(trx->signals);

	while (sig != NULL) {
		next_sig = UT_LIST_GET_NEXT(signals, sig);

		if (sig->type == TRX_SIG_COMMIT) {

			trx_sig_reply(sig, next_thr);
			trx_sig_remove(trx, sig);
		}

		sig = next_sig;
	}

	trx->que_state = TRX_QUE_RUNNING;
}
