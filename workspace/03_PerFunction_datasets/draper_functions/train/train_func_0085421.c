gkrellm_alert_plugin_add(GkrellmMonitor *mon, gchar *name)
	{
	GkrellmAlertPlugin	*gap;

	if (!mon || !name || !*name)
		return NULL;
	gap = g_new0(GkrellmAlertPlugin, 1);
	gap->mon = mon;
	gap->name = g_strdup(name);
	alert_plugin_list = g_list_append(alert_plugin_list, gap);
	return gap;
	}
