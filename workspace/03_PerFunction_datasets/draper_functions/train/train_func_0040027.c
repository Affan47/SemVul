trx_owns_prepare_commit_mutex_set(

	trx_t*	trx)
{
	ut_a(trx_is_registered_for_2pc(trx));
	trx->owns_prepare_mutex = 1;
}
