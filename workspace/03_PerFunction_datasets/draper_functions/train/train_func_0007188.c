slayer_server_log_close(slayer_server_log_manager_t *manager) {
	if (manager->fhandle) {
		apr_thread_mutex_destroy(manager->file_mutex);
		apr_file_close(manager->fhandle);
		apr_pool_destroy(manager->mpool);
	}
	return 0;
}
