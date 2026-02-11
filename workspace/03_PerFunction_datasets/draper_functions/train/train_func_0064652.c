gkrellm_init_host_monitor(void)
	{
	gchar	**parts;

	style_id = gkrellm_add_meter_style(&monitor_host, HOST_STYLE_NAME);

	if (_GK.client_mode)
		{
		hostname = _GK.server_hostname;
		system_name = g_strdup(_GK.server_sysname);
		}
	else
		{
		hostname = gkrellm_sys_get_host_name();
		system_name = g_strdup(gkrellm_sys_get_system_name());
		}
	parts = g_strsplit(system_name, " ", 2);
	kname_dtext.string = parts[0];
	kversion_dtext.string = parts[1];
	hostname_can_shorten = strchr(hostname, (int) '.') ? TRUE : FALSE;

	mon_host = &monitor_host;
	return &monitor_host;
	}
