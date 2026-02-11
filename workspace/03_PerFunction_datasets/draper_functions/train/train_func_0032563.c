ibuildable_set_command (IAnjutaBuildable *manager,
						IAnjutaBuildableCommand command_id,
						const gchar *command_override, GError **err)
{
	BasicAutotoolsPlugin *plugin = ANJUTA_PLUGIN_BASIC_AUTOTOOLS (manager);
	if (plugin->commands[command_id])
		g_free (plugin->commands[command_id]);
	plugin->commands[command_id] = g_strdup (command_override);
}
