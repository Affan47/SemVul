adjust_sensors_display(CpuMon *cpu, gint force)
	{
	GkrellmPanel	*p;
	GkrellmDecal	*ds, *df;
	GkrellmAlert	*alert;
	gint			position = 0;

	ds = cpu->sensor_decal;
	df = cpu->fan_decal;
	if (!ds || !df)
		return FALSE;


	p = cpu->chart->panel;
	cpu->show_temperature = cpu->show_fan = FALSE;
	if (!_GK.demo)
		{
		gkrellm_sensor_alert_connect(cpu->sensor_temp,
					cb_cpu_temp_alert_trigger, cpu);
		gkrellm_sensor_alert_connect(cpu->sensor_fan,
					cb_cpu_fan_alert_trigger, cpu);
		}


	alert = gkrellm_sensor_alert(cpu->sensor_fan);
	gkrellm_reset_alert_soft(alert);

	if (cpu->sensor_temp || _GK.demo)
		cpu->show_temperature = TRUE;
	if (cpu->sensor_fan || _GK.demo)
		cpu->show_fan = TRUE;

	if (cpu->show_temperature || cpu->show_fan)
		{
		if (! gkrellm_is_decal_visible(ds) || force)
			gkrellm_make_decal_visible(p, ds);
		position = 0;
		}
	else
		{
		if (gkrellm_is_decal_visible(ds) || force)
			gkrellm_make_decal_invisible(p, ds);
		position = cpu->save_label_position;
		}
	if (cpu->show_fan && cpu->show_temperature && sensor_separate_mode)
		{
		if (! gkrellm_is_decal_visible(df) || force)
			gkrellm_make_decal_visible(p, df);
		position = -1;
		}
	else
		{
		if (gkrellm_is_decal_visible(df) || force)
			gkrellm_make_decal_invisible(p, df);
		}
	if (position != p->label->position || force)
		{
		if (cpu->save_label_position >= 0)
			p->label->position = position;
		gkrellm_draw_panel_label(p);
		draw_sensor_decals(cpu);
		gkrellm_draw_panel_layers(p);
		}
	return TRUE;
	}
