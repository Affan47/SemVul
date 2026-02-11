hexchat_plugin_init (hexchat_plugin *plugin_handle, char **plugin_name, char **plugin_desc, char **plugin_version, char *arg)
{
	ph = plugin_handle;

	*plugin_name = name;
	*plugin_desc = desc;
	*plugin_version = version;


	if (hexchat_pluginpref_get_int (ph, "limit") == -1)
	{
		hexchat_pluginpref_set_int (ph, "limit", DEFAULT_LIMIT);
	}

	hexchat_hook_command (ph, "CHECKSUM", HEXCHAT_PRI_NORM, checksum, "Usage: /CHECKSUM GET|SET", 0);
	hexchat_hook_print (ph, "DCC RECV Complete", HEXCHAT_PRI_NORM, dccrecv_cb, NULL);
	hexchat_hook_print (ph, "DCC Offer", HEXCHAT_PRI_NORM, dccoffer_cb, NULL);

	hexchat_printf (ph, "%s plugin loaded\n", name);
	return 1;
}
