plugin_register(struct plugin_handle* plugin, const char* config)
{
	PLUGIN_INITIALIZE(plugin, "SQLite authentication plugin", "1.0", "Authenticate users based on a SQLite database.");


	plugin->funcs.auth_get_user = get_user;
	plugin->funcs.auth_register_user = register_user;
	plugin->funcs.auth_update_user = update_user;
	plugin->funcs.auth_delete_user = delete_user;

	plugin->ptr = parse_config(config, plugin);
	if (plugin->ptr)
		return 0;
	return -1;
}
