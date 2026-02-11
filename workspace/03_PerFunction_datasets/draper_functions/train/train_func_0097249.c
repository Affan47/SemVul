save_battery_config(FILE *f)
	{
	GList	*list;
	Battery	*bat;

	fprintf(f, "%s enable %d\n", BAT_CONFIG_KEYWORD, enable_each);
	fprintf(f, "%s enable_composite %d\n", BAT_CONFIG_KEYWORD,
					enable_composite);
	fprintf(f, "%s estimate_time %d\n", BAT_CONFIG_KEYWORD, enable_estimate);


	fprintf(f, "%s estimate_time_discharge %.0f\n", BAT_CONFIG_KEYWORD,
				estimate_runtime[0] * GKRELLM_FLOAT_FACTOR);
	fprintf(f, "%s estimate_time_charge %.0f\n", BAT_CONFIG_KEYWORD,
				estimate_runtime[1] * GKRELLM_FLOAT_FACTOR);
	fprintf(f, "%s estimate_time_charge_model %d\n", BAT_CONFIG_KEYWORD,
				estimate_model[1]);
	fprintf(f, "%s full_cap_fallback %d\n", BAT_CONFIG_KEYWORD,
						full_cap_fallback);
	if (!_GK.client_mode)
		fprintf(f, "%s poll_interval %d\n", BAT_CONFIG_KEYWORD, poll_interval);
	if (launch.command)
		fprintf(f, "%s launch1 %s\n", BAT_CONFIG_KEYWORD, launch.command);
	if (launch.tooltip_comment)
		fprintf(f, "%s tooltip_comment %s\n",
					BAT_CONFIG_KEYWORD, launch.tooltip_comment);
	fprintf(f, "%s alert_units_percent %d\n", BAT_CONFIG_KEYWORD,
				alert_units_percent);
	for (list = battery_list; list; list = list->next)
		{
		bat = (Battery *) list->data;
		if (bat == composite_battery)
			fprintf(f, "%s display_mode_composite %d %d\n", BAT_CONFIG_KEYWORD,
						bat->display_mode, bat->id);
		else
			fprintf(f, "%s display_mode %d %d\n", BAT_CONFIG_KEYWORD,
						bat->display_mode, bat->id);
		}
	gkrellm_save_alertconfig(f, bat_alert, BAT_CONFIG_KEYWORD, NULL);
	}
