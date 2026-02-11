save_cpu_config(FILE *f)
	{
	GList	*list;
	CpuMon	*cpu;

	for (list = cpu_mon_list; list; list = list->next)
		{
		cpu = (CpuMon *) list->data;
		if (*(cpu->launch.command) != '\0')
			fprintf(f, "%s launch %s %s\n", CPU_CONFIG_KEYWORD,
						cpu->name, cpu->launch.command);
		if (*(cpu->launch.tooltip_comment) != '\0')
			fprintf(f, "%s tooltip_comment %s %s\n", CPU_CONFIG_KEYWORD,
						cpu->name, cpu->launch.tooltip_comment);
		fprintf(f, "%s extra_info %s %d\n", CPU_CONFIG_KEYWORD,
					cpu->name, cpu->extra_info);
		gkrellm_save_chartconfig(f, cpu->chart_config,
					CPU_CONFIG_KEYWORD, cpu->name);
		}
	fprintf(f, "%s enable %d\n", CPU_CONFIG_KEYWORD, cpu_enabled);
	fprintf(f, "%s smp_mode %d\n", CPU_CONFIG_KEYWORD, smp_mode);
	fprintf(f, "%s omit_nice_mode %d\n", CPU_CONFIG_KEYWORD, omit_nice_mode);
	fprintf(f, "%s config_tracking %d\n", CPU_CONFIG_KEYWORD, config_tracking);
	fprintf(f, "%s sensor_mode %d\n", CPU_CONFIG_KEYWORD,
			sensor_separate_mode);
	fprintf(f, "%s text_format %s\n", CPU_CONFIG_KEYWORD, text_format);
	if (cpu_alert)
		{
		gkrellm_save_alertconfig(f, cpu_alert, CPU_CONFIG_KEYWORD, NULL);
		fprintf(f, "%s alert_includes_nice %d\n", CPU_CONFIG_KEYWORD,
					alert_includes_nice);
		}
	}
