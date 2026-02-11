trx_roll_savepoint_free(

	trx_t*			trx,
	trx_named_savept_t*	savep)
{
	ut_a(savep != NULL);
	ut_a(UT_LIST_GET_LEN(trx->trx_savepoints) > 0);

	UT_LIST_REMOVE(trx_savepoints, trx->trx_savepoints, savep);
	mem_free(savep->name);
	mem_free(savep);
}
