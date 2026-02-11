serve_cpu_data(GkrellmdMonitor *mon, gboolean first_serve)
	{
	CpuData	*cpu;
	GList	*list;
	gchar	buf[128];

	gkrellmd_set_serve_name(mon, "cpu");
	for (list = cpu_list; list; list = list->next)
		{
		cpu = (CpuData *) list->data;
		snprintf(buf, sizeof(buf), "%d %lu %lu %lu %lu\n", cpu->instance,
				cpu->user, cpu->nice, cpu->sys, cpu->idle);
		gkrellmd_serve_data(mon, buf);
		}
	}
