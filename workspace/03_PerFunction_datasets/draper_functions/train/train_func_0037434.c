dbslayer_log_add_error(dbslayer_log_manager_t *manager, apr_pool_t *mpool,
			const char *client_ip,apr_int64_t rtime,
			const char *request_line, const char *error_msg ) {

	json_value *container = json_create_object(mpool);
	json_add_object(container,"client_ip",json_create_string(mpool,client_ip));
	json_add_object(container,"request_time",json_create_long(mpool,rtime / (1000*1000)));
	json_add_object(container,"request",json_create_string(mpool,request_line));
	json_add_object(container,"error",json_create_string(mpool,error_msg));
	char *json_entry = strdup(json_serialize(mpool,container));

	apr_thread_mutex_lock(manager->list_mutex);
	manager->offset++;
	if(manager->offset == manager->nentries)  manager->offset = 0;
	free(manager->entries[manager->offset].json_view);
	manager->entries[manager->offset].json_view = json_entry;
	apr_thread_mutex_unlock(manager->list_mutex);
}
