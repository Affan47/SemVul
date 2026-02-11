__ast_data_register(const char *path, const struct ast_data_handler *handler,
	const char *registrar, struct ast_module *mod)
{
	struct data_provider *node;

	if (!path) {
		return -1;
	}


	if (!data_structure_compatible(handler->version,
		latest_handler_compatible_version,
		current_handler_version)) {
		return -1;
	}


	data_write_lock();

	node = data_provider_create(root_data.container, path, registrar);
	if (!node) {
		ast_log(LOG_ERROR, "Unable to create the specified path (%s) "
			"for '%s'.\n", path, registrar);
		data_unlock();
		return -1;
	}

	if (ao2_container_count(node->children) || node->handler) {
		ast_log(LOG_ERROR, "The node '%s' was already registered. "
			"We were unable to register '%s' for registrar '%s'.\n",
			node->name, path, registrar);
		ao2_ref(node, -1);
		data_unlock();
		return -1;
	}


	node->handler = handler;
	node->module = mod;

	ao2_ref(node, -1);

	data_unlock();

	return 0;
}
