cb_smp_mode(GtkWidget *button, gpointer data)
	{
	GList		*list;
	CpuMon		*cpu;
	gint		i = GPOINTER_TO_INT(data);
	gboolean	prev_enabled, rebuild_temps = FALSE, rebuild_fans = FALSE;

	if (GTK_TOGGLE_BUTTON(button)->active)
		smp_mode = i;
	for (list = cpu_mon_list; list; list = list->next)
		{
		cpu = (CpuMon *) list->data;
		prev_enabled = cpu->enabled;
		if (enable_cpu_visibility(cpu) && cpu->enabled)
			gkrellm_reset_and_draw_chart(cpu->chart);
		if (prev_enabled && !cpu->enabled)
			{
			if (cpu->sensor_temp)
				{
				gkrellm_sensor_reset_location(cpu->sensor_temp);
				rebuild_temps |= TRUE;
				}
			if (cpu->sensor_fan)
				{
				gkrellm_sensor_reset_location(cpu->sensor_fan);
				rebuild_fans |= TRUE;
				}
			cpu->sensor_temp = NULL;
			cpu->sensor_fan = NULL;
			fix_panel(cpu);
			}
		gkrellm_apply_launcher(&cpu->launch_entry, &cpu->tooltip_entry,
					cpu->chart->panel, &cpu->launch, gkrellm_launch_button_cb);
		}
	if (rebuild_temps || rebuild_fans)
		gkrellm_sensors_rebuild(rebuild_temps, rebuild_fans, FALSE);
	}
