_unload_module(int fromload)
{
	if (!smdi_loaded) {
		return 0;
	}


	ASTOBJ_CONTAINER_DESTROYALL(&smdi_ifaces, ast_smdi_interface_destroy);
	ASTOBJ_CONTAINER_DESTROY(&smdi_ifaces);

	destroy_all_mailbox_mappings();

	ast_mutex_lock(&mwi_monitor.lock);
	mwi_monitor.stop = 1;
	ast_cond_signal(&mwi_monitor.cond);
	ast_mutex_unlock(&mwi_monitor.lock);

	if (mwi_monitor.thread != AST_PTHREADT_NULL) {
		pthread_join(mwi_monitor.thread, NULL);
	}

	if (!fromload) {
		ast_custom_function_unregister(&smdi_msg_retrieve_function);
		ast_custom_function_unregister(&smdi_msg_function);
	}

	smdi_loaded = 0;
	return 0;
}
