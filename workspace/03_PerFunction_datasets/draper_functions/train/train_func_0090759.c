client_monitor_setup(gchar *line)
	{
	void			(*func)();
	gchar			buf[64];
	gint			i;
	gboolean		found_builtin = FALSE;

	if (!*line || setup_done)
		return;
	for (i = 0; i < sizeof(monitor_table) / sizeof(KeyTable); ++i)
		{
		if (!strcmp(line, monitor_table[i].key))
			{
			func = monitor_table[i].func;
			(*func)();
			found_builtin = TRUE;
			break;
			}
		}


	if (!found_builtin)
		{
		snprintf(buf, sizeof(buf), "%s available", line);
		client_plugin_add_setup_line(buf);
		}
	}
