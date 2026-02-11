trx_general_rollback_for_mysql(

	trx_t*		trx,
	trx_savept_t*	savept)


{
	mem_heap_t*	heap;
	que_thr_t*	thr;
	roll_node_t*	roll_node;


	srv_active_wake_master_thread();

	trx_start_if_not_started(trx);

	heap = mem_heap_create(512);

	roll_node = roll_node_create(heap);

	if (savept) {
		roll_node->partial = TRUE;
		roll_node->savept = *savept;
	}

	trx->error_state = DB_SUCCESS;

	thr = pars_complete_graph_for_exec(roll_node, trx, heap);

	ut_a(thr == que_fork_start_command(que_node_get_parent(thr)));
	que_run_threads(thr);

	mutex_enter(&kernel_mutex);

	while (trx->que_state != TRX_QUE_RUNNING) {

		mutex_exit(&kernel_mutex);

		os_thread_sleep(100000);

		mutex_enter(&kernel_mutex);
	}

	mutex_exit(&kernel_mutex);

	mem_heap_free(heap);

	ut_a(trx->error_state == DB_SUCCESS);


	srv_active_wake_master_thread();

	return((int) trx->error_state);
}
