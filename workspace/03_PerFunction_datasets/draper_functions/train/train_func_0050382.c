dbus_plugin_init (hexchat_plugin *plugin_handle,
		  char **plugin_name,
		  char **plugin_desc,
		  char **plugin_version,
		  char *arg)
{
	ph = plugin_handle;
	*plugin_name = PNAME;
	*plugin_desc = PDESC;
	*plugin_version = PVERSION;

	if (init_dbus()) {


		clients = g_hash_table_new_full (g_str_hash,
						 g_str_equal,
						 g_free,
						 g_object_unref);

		hexchat_hook_print (ph, "Open Context",
				  HEXCHAT_PRI_NORM,
				  open_context_cb,
				  NULL);

		hexchat_hook_print (ph, "Close Context",
				  HEXCHAT_PRI_NORM,
				  close_context_cb,
				  NULL);

		hexchat_hook_command (ph, "unload",
				    HEXCHAT_PRI_HIGHEST,
				    unload_plugin_cb, NULL, NULL);
	}

	return TRUE;
}
