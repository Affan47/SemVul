gkrellm_cpu_get_sensor_panel_label(gint n)
	{
	CpuMon	*cpu;
	gchar	*s = "cpu?";

	cpu = (CpuMon *) g_list_nth_data(cpu_mon_list, n);
	if (cpu)
		s = cpu->panel_label;
	return s;
	}
