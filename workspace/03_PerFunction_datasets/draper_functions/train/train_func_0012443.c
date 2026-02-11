dleyna_connector_mgr_load(const gchar *name)
{
	GModule *module;
	const dleyna_connector_t *connector;
	dleyna_connector_get_interface_t get_interface;
	gchar *path;

	DLEYNA_LOG_DEBUG("Enter");

	path = g_strdup_printf("%s/%s%s.so", CONNECTOR_DIR,
			       DLEYNA_CONNECTOR_LIB_PATTERN, name);
	module = g_module_open(path, G_MODULE_BIND_LAZY);
	g_free(path);

	if (module) {
		if (!g_connectors)
			g_connectors = g_hash_table_new(g_direct_hash,
							g_direct_equal);

		if (g_module_symbol(module, "dleyna_connector_get_interface",
				    (gpointer *)&get_interface)) {
			connector = get_interface();
			g_hash_table_insert(g_connectors, (gpointer)connector,
					    module);
		} else {
			connector = NULL;
			g_module_close(module);
			DLEYNA_LOG_CRITICAL(
					"Connector '%s' entry point not found",
					name);
		}

	} else {
		connector = NULL;
		DLEYNA_LOG_CRITICAL("Connector '%s' not found", name);
	}

	DLEYNA_LOG_DEBUG("Exit");

	return connector;
}
