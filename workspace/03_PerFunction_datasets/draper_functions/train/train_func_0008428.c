trx_sig_remove(

	trx_t*		trx,
	trx_sig_t*	sig)
{
	ut_ad(trx && sig);
	ut_ad(mutex_own(&kernel_mutex));

	ut_ad(sig->receiver == NULL);

	UT_LIST_REMOVE(signals, trx->signals, sig);
	sig->type = 0;

	if (sig != &(trx->sig)) {
		mem_free(sig);
	}
}
