plugin_open(const char* filename)
{
	struct uhub_plugin* plugin;
	LOG_PLUGIN("plugin_open: \"%s\"", filename);

	plugin = (struct uhub_plugin*) hub_malloc_zero(sizeof(struct uhub_plugin));
	if (!plugin)
	{
		return 0;
	}

#ifdef HAVE_DLOPEN
	plugin->handle = dlopen(filename, RTLD_LAZY);
#else
	plugin->handle = LoadLibraryExA(filename, NULL, 0);
#endif

	if (!plugin->handle)
	{
#ifdef HAVE_DLOPEN
		LOG_ERROR("Unable to open plugin %s: %s", filename, dlerror());
#else
		LOG_ERROR("Unable to open plugin %s: %d", filename, GetLastError());
#endif
		hub_free(plugin);
		return 0;
	}

	plugin->filename = strdup(filename);
	plugin->internals = hub_malloc_zero(sizeof(struct plugin_hub_internals));
	return plugin;
}
