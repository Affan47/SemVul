plugin_initialize(struct hub_config* config, struct hub_info* hub)
{
	int ret;

	hub->plugins->loaded = list_create();
	if (!hub->plugins->loaded)
		return -1;

	if (config)
	{
		if (!*config->file_plugins)
			return 0;

		ret = file_read_lines(config->file_plugins, hub, &plugin_parse_line);
		if (ret == -1)
		{
			list_clear(hub->plugins->loaded, hub_free);
			list_destroy(hub->plugins->loaded);
			hub->plugins->loaded = 0;
			return -1;
		}
	}
	return 0;
}
