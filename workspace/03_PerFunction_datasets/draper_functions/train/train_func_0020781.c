plugin_unregister(struct plugin_handle* plugin)
{
	struct welcome_data* data = (struct welcome_data*) plugin->ptr;

	if (data->cmd_motd)
		plugin->hub.command_del(plugin, data->cmd_motd);

	if (data->cmd_rules)
		plugin->hub.command_del(plugin, data->cmd_rules);

	free_welcome_data(data);
	return 0;
}
