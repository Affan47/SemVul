trx_commit_for_mysql(

	trx_t*	trx)
{


	ut_a(trx);

	trx_start_if_not_started(trx);

	trx->op_info = "committing";

	mutex_enter(&kernel_mutex);

	trx_commit_off_kernel(trx);

	mutex_exit(&kernel_mutex);

	trx->op_info = "";

	return(DB_SUCCESS);
}
