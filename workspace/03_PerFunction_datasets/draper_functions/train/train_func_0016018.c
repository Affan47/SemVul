save_meminfo_config(FILE *f)
	{
	fprintf(f, "%s mem_meter %d %d %d\n", MEM_CONFIG_KEYWORD,
				mem.enabled, mem.label_is_data, mem.all_krells);
	fprintf(f, "%s swap_meter %d %d\n", MEM_CONFIG_KEYWORD,
				swap.enabled, swap.label_is_data);
	fprintf(f, "%s swap_chart %d %d\n", MEM_CONFIG_KEYWORD,
				swap_chart.enabled, swap_chart.extra_info);
	gkrellm_save_chartconfig(f, swap_chart.chart_config,
				MEM_CONFIG_KEYWORD, NULL);

	fprintf(f, "%s mem_launch %s\n", MEM_CONFIG_KEYWORD,
				mem.launch.command);
	fprintf(f, "%s mem_tooltip %s\n", MEM_CONFIG_KEYWORD,
				mem.launch.tooltip_comment);
	fprintf(f, "%s mem_data_format %s\n", MEM_CONFIG_KEYWORD,mem.data_format);

	fprintf(f, "%s swap_launch %s\n", MEM_CONFIG_KEYWORD,
				swap.launch.command);
	fprintf(f, "%s swap_tooltip %s\n", MEM_CONFIG_KEYWORD,
				swap.launch.tooltip_comment);
	fprintf(f, "%s swap_data_format %s\n", MEM_CONFIG_KEYWORD,
				swap.data_format);

	fprintf(f, "%s text_format %s\n", MEM_CONFIG_KEYWORD, text_format);

	if (mem.alert)
		gkrellm_save_alertconfig(f, mem.alert, MEM_CONFIG_KEYWORD, "mem");
	if (swap.alert)
		gkrellm_save_alertconfig(f, swap.alert, MEM_CONFIG_KEYWORD, "swap");
	}
