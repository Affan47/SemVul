gkrellm_save_alertconfig(FILE *f, GkrellmAlert *alert,
			gchar *mon_keyword, gchar *name)
	{
	GList					*list;
	GkrellmAlertPlugin		*gap;
	GkrellmAlertPluginLink	*apl;
	gchar					*s, *p;

	if (!f || !alert || !mon_keyword)
		return;
	if (name)
		s = g_strdup_printf("%s %s %s ", mon_keyword,
				GKRELLM_ALERTCONFIG_KEYWORD, name);
	else
		s = g_strdup_printf("%s %s ", mon_keyword,GKRELLM_ALERTCONFIG_KEYWORD);

	if (alert->alarm_command && *alert->alarm_command)
		fprintf(f, "%s alarm_command %s\n", s, alert->alarm_command);
	if (alert->warn_command && *alert->warn_command)
		fprintf(f, "%s warn_command %s\n", s, alert->warn_command);
	fprintf(f, "%s values %d %d %d %d\n", s, alert->do_panel_updates,
			alert->check_high, alert->check_low, alert->check_hardwired);
	fprintf(f, "%s repeat %d %d\n", s, alert->alarm_repeat_set,
			alert->warn_repeat_set);


	fprintf(f, "%s limits %.0f %.0f %.0f %.0f\n", s,
				alert->high.alarm_limit * GKRELLM_FLOAT_FACTOR,
				alert->high.warn_limit  * GKRELLM_FLOAT_FACTOR,
				alert->low.warn_limit   * GKRELLM_FLOAT_FACTOR,
				alert->low.alarm_limit  * GKRELLM_FLOAT_FACTOR);
	if (alert->delay_step > 0)
		fprintf(f, "%s delay %d %d %d %d\n", s, alert->delay,
					alert->delay_high, alert->delay_low, alert->delay_step);


	g_free(alert->id_string);
	p = name;
	if (p && *p == '"')
		++p;
	alert->id_string = g_strconcat(mon_keyword, p ? "-" : NULL, p, NULL);
	if ((p = strrchr(alert->id_string, '"')) != NULL)
		*p = '\0';
	for (p = alert->id_string; *p; ++p)
		if (*p == '/' || *p == ' ')
			*p = '-';
	fprintf(f, "%s id_string %s\n", s, alert->id_string);

	for (list = alert->plugin_list; list; list = list->next)
		{
		apl = (GkrellmAlertPluginLink *) list->data;
		gap = apl->alert_plugin;
		if (MONITOR_ENABLED(gap->mon) && gap->config_save_func)
			{
			p = g_strconcat(s, "plugin ", gap->name, NULL);
			(*gap->config_save_func)(alert, apl->data, f, p, alert->id_string);
			g_free(p);
			}
		}
	g_free(s);
	}
