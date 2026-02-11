load_module(void)
{
	if (!(cache = ao2_container_alloc(573, cache_hash, cache_cmp))) {
		return AST_MODULE_LOAD_FAILURE;
	}

	if (ast_pthread_create(&cleanup_thread, NULL, cleanup, NULL)) {
		return AST_MODULE_LOAD_FAILURE;
	}

	if (ast_register_switch(&realtime_switch))
		return AST_MODULE_LOAD_FAILURE;
	return AST_MODULE_LOAD_SUCCESS;
}
