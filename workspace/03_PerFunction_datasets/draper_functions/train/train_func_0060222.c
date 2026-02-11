load_all_nic_libraries()
{
	int rc, i = 0;
	nic_lib_handle_t *handle;

	for (i = 0; i < sizeof(nic_get_ops) / sizeof(nic_get_ops[0]); i++) {

		handle = alloc_nic_library_handle();
		if (handle == NULL) {
			LOG_ERR("Could not allocate memory for CNIC nic lib");
			return -ENOMEM;
		}

		handle->ops = (*nic_get_ops[i]) ();

		rc = load_nic_library(handle);
		if (rc != 0) {
			free_nic_library_handle(handle);
			return rc;
		}

		pthread_mutex_lock(&nic_lib_list_mutex);


		if (nic_lib_list == NULL) {
			nic_lib_list = handle;
		} else {
			nic_lib_handle_t *current = nic_lib_list;

			while (current->next != NULL)
				current = current->next;

			current->next = handle;
		}
		pthread_mutex_unlock(&nic_lib_list_mutex);

		LOG_DEBUG("Added '%s' nic library", handle->ops->description);
	}

	return rc;
}
