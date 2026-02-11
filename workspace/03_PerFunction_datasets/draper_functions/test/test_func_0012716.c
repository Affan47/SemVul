gkrellm_client_plugin_serve_data_connect(GkrellmMonitor *mon,
			gchar *key_name, void (*func_cb)(gchar *line))
	{
	ClientPlugin	*plug;

	if (!mon || !key_name || !func_cb)
		return;
	plug = g_new0(ClientPlugin, 1);
	plug->mon = mon;
	plug->key_name = g_strdup(key_name);
	plug->func_cb = func_cb;
	client_plugin_serve_data_list
				= g_list_append(client_plugin_serve_data_list, plug);

	client_plugin_initial_update(plug);
	}
