plugin_init(Plugin *plugin)
{
	GeanyPlugin **p_geany_plugin;
	PluginCallback *callbacks;
	PluginInfo **p_info;
	PluginFields **plugin_fields;


	g_module_symbol(plugin->module, "geany_plugin", (void *) &p_geany_plugin);
	if (p_geany_plugin)
		*p_geany_plugin = &plugin->public;
	g_module_symbol(plugin->module, "plugin_info", (void *) &p_info);
	if (p_info)
		*p_info = &plugin->info;
	g_module_symbol(plugin->module, "plugin_fields", (void *) &plugin_fields);
	if (plugin_fields)
		*plugin_fields = &plugin->fields;
	read_key_group(plugin);


	g_return_if_fail(plugin->init);
	plugin->init(&geany_data);


	g_module_symbol(plugin->module, "plugin_configure", (void *) &plugin->configure);
	g_module_symbol(plugin->module, "plugin_configure_single", (void *) &plugin->configure_single);
	if (app->debug_mode && plugin->configure && plugin->configure_single)
		g_warning("Plugin '%s' implements plugin_configure_single() unnecessarily - "
			"only plugin_configure() will be used!",
			plugin->info.name);

	g_module_symbol(plugin->module, "plugin_help", (void *) &plugin->help);
	g_module_symbol(plugin->module, "plugin_cleanup", (void *) &plugin->cleanup);
	if (plugin->cleanup == NULL)
	{
		if (app->debug_mode)
			g_warning("Plugin '%s' has no plugin_cleanup() function - there may be memory leaks!",
				plugin->info.name);
	}


	if (plugin->fields.flags & PLUGIN_IS_DOCUMENT_SENSITIVE)
	{
		ui_add_document_sensitive(plugin->fields.menu_item);
	}

	g_module_symbol(plugin->module, "plugin_callbacks", (void *) &callbacks);
	if (callbacks)
		add_callbacks(plugin, callbacks);


	active_plugin_list = g_list_insert_sorted(active_plugin_list, plugin, cmp_plugin_names);

	geany_debug("Loaded:   %s (%s)", plugin->filename,
		NVL(plugin->info.name, "<Unknown>"));
}
