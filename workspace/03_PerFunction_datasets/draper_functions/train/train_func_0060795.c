adjust_sensors_display(gint force)
	{
	GkrellmPanel	*p;
	GkrellmDecal	*ds, *df;
	GkrellmAlert	*alert;
	gint			position	= 0;

	ds = proc.sensor_decal;
	df = proc.fan_decal;
	if (!ds || !df)
		return FALSE;


	p = proc.chart->panel;
	show_temperature = show_fan = FALSE;
	if (!_GK.demo)
		{
		gkrellm_sensor_alert_connect(proc.sensor_temp,
					cb_mb_temp_alert_trigger, &proc);
		gkrellm_sensor_alert_connect(proc.sensor_fan,
					cb_mb_fan_alert_trigger, &proc);
		}


	alert = gkrellm_sensor_alert(proc.sensor_fan);
	gkrellm_reset_alert_soft(alert);

	if (proc.sensor_temp || _GK.demo)
		show_temperature = TRUE;
	if (proc.sensor_fan || _GK.demo)
		show_fan = TRUE;

	if (show_temperature || show_fan)
		{
		if (! gkrellm_is_decal_visible(ds) || force)
			gkrellm_make_decal_visible(p, ds);
		position = 0;
		}
	else
		{
		if (gkrellm_is_decal_visible(ds) || force)
			gkrellm_make_decal_invisible(p, ds);
		position = proc.save_label_position;
		}
	if (show_fan && show_temperature && sensor_separate_mode)
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
		if (proc.save_label_position >= 0)
			p->label->position = position;
		gkrellm_draw_panel_label(p);
		draw_sensor_decals();
		gkrellm_draw_panel_layers(p);
		}
	return TRUE;
	}
