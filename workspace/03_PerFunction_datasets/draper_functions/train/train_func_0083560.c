plugin_command_dispatch(struct command_base* cbase, struct hub_user* user, struct hub_command* cmd)
{
	struct plugin_handle* plugin = (struct plugin_handle*) cmd->ptr;
	struct plugin_callback_data* data = get_callback_data(plugin);
	struct plugin_command_handle* cmdh;
	struct plugin_user* puser = (struct plugin_user*) user;
	struct plugin_command* pcommand = (struct plugin_command*) cmd;

	LOG_PLUGIN("plugin_command_dispatch: cmd=%s", cmd->prefix);

	LIST_FOREACH(struct plugin_command_handle*, cmdh, data->commands,
	{
		if (strcmp(cmdh->prefix, cmd->prefix) == 0)
			return cmdh->handler(plugin, puser, pcommand);
	});
	return 0;
}
