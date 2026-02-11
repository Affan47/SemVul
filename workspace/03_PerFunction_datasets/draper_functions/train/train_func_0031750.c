plugin_new(const gchar *fname, gboolean init_plugin, gboolean add_to_list)
{
	Plugin *plugin;
	GModule *module;
	GeanyData **p_geany_data;
	GeanyFunctions **p_geany_functions;
	void (*plugin_set_info)(PluginInfo*);

	g_return_val_if_fail(fname, NULL);
	g_return_val_if_fail(g_module_supported(), NULL);


	plugin = find_active_plugin_by_name(fname);
	if (plugin != NULL)
	{
		geany_debug("Plugin \"%s\" already loaded.", fname);
		if (add_to_list)
		{

			if (g_list_find(plugin_list, plugin) != NULL)
				return NULL;

			plugin_list = g_list_prepend(plugin_list, plugin);
		}
		return plugin;
	}


	module = g_module_open(fname, G_MODULE_BIND_LOCAL);
	if (! module)
	{
		geany_debug("Can't load plugin: %s", g_module_error());
		return NULL;
	}

	if (plugin_loaded(module))
	{
		geany_debug("Plugin \"%s\" already loaded.", fname);

		if (! g_module_close(module))
			g_warning("%s: %s", fname, g_module_error());
		return NULL;
	}

	if (! plugin_check_version(module))
	{
		if (! g_module_close(module))
			g_warning("%s: %s", fname, g_module_error());
		return NULL;
	}

	g_module_symbol(module, "plugin_set_info", (void *) &plugin_set_info);
	if (plugin_set_info == NULL)
	{
		geany_debug("No plugin_set_info() defined for \"%s\" - ignoring plugin!", fname);

		if (! g_module_close(module))
			g_warning("%s: %s", fname, g_module_error());
		return NULL;
	}

	plugin = g_new0(Plugin, 1);


	g_module_symbol(module, "geany_data", (void *) &p_geany_data);
	if (p_geany_data)
		*p_geany_data = &geany_data;
	g_module_symbol(module, "geany_functions", (void *) &p_geany_functions);
	if (p_geany_functions)
		*p_geany_functions = &geany_functions;


	plugin_set_info(&plugin->info);
	if (G_UNLIKELY(! NZV(plugin->info.name)))
	{
		geany_debug("No plugin name set in plugin_set_info() for \"%s\" - ignoring plugin!",
			fname);

		if (! g_module_close(module))
			g_warning("%s: %s", fname, g_module_error());
		g_free(plugin);
		return NULL;
	}

	g_module_symbol(module, "plugin_init", (void *) &plugin->init);
	if (plugin->init == NULL)
	{
		geany_debug("Plugin '%s' has no plugin_init() function - ignoring plugin!",
			plugin->info.name);

		if (! g_module_close(module))
			g_warning("%s: %s", fname, g_module_error());
		g_free(plugin);
		return NULL;
	}


	plugin->filename = g_strdup(fname);
	plugin->module = module;
	plugin->public.info = &plugin->info;
	plugin->public.priv = plugin;

	if (init_plugin)
		plugin_init(plugin);

	if (add_to_list)
		plugin_list = g_list_prepend(plugin_list, plugin);

	return plugin;
}
