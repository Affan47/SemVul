unload_module(void)
{
	struct lock_frame *current;


	unloading = 1;

	AST_LIST_LOCK(&locklist);
	while ((current = AST_LIST_REMOVE_HEAD(&locklist, entries))) {

		if (current->owner || ao2_container_count(current->requesters)) {

			AST_LIST_INSERT_HEAD(&locklist, current, entries);
			AST_LIST_UNLOCK(&locklist);
			unloading = 0;
			return -1;
		}
		ast_mutex_destroy(&current->mutex);
		ao2_ref(current->requesters, -1);
		ast_free(current);
	}


	ast_custom_function_unregister(&lock_function);
	ast_custom_function_unregister(&trylock_function);
	ast_custom_function_unregister(&unlock_function);

	if (broker_tid != AST_PTHREADT_NULL) {
		pthread_cancel(broker_tid);
		pthread_kill(broker_tid, SIGURG);
		pthread_join(broker_tid, NULL);
	}

	AST_LIST_UNLOCK(&locklist);

	return 0;
}
