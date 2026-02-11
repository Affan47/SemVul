ibuildable_reset_commands (IAnjutaBuildable *manager, GError **err)
{
	gint i;
	BasicAutotoolsPlugin *ba_plugin = ANJUTA_PLUGIN_BASIC_AUTOTOOLS (manager);

	for (i = 0; i < IANJUTA_BUILDABLE_N_COMMANDS; i++)
	{
		g_free (ba_plugin->commands[i]);
		ba_plugin->commands[i] = NULL;
	}
}
