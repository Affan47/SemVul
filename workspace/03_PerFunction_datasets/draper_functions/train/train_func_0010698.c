gkrellm_alert_plugin_alert_detach(GkrellmAlertPlugin *gap, GkrellmAlert *alert)
	{
	GList					*list;
	GkrellmAlertPluginLink	*apl;

	if (!gap || !alert)
		return;
	for (list = alert->plugin_list; list; list = list->next)
		{
		apl = (GkrellmAlertPluginLink *) list->data;
		if (apl->alert_plugin == gap)
			{
			alert->plugin_list = g_list_remove(alert->plugin_list, apl);
			g_free(apl);
			break;
			}
		}
	}
