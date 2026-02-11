gsd_wacom_device_add_buttons_dir (WacomDevice      *wacom_device,
				  const char       *settings_path,
				  WacomButtonFlags  direction,
				  const char       *button_str,
				  const char       *button_str_id)
{
	GList *l;
	guint num_buttons, i, button_num;
	char *name, *id;

	l = NULL;
	button_num = 1;
	num_buttons = libwacom_get_num_buttons (wacom_device);
	for (i = 'A'; i < 'A' + num_buttons; i++) {
		WacomButtonFlags flags;

		flags = libwacom_get_button_flag (wacom_device, i);
		if (!(flags & direction))
			continue;

		if (flags & WACOM_BUTTON_MODESWITCH)
			continue;

		name = g_strdup_printf (button_str, button_num++);
		id = g_strdup_printf ("%s%c", button_str_id, i);
		l = g_list_append (l, gsd_wacom_tablet_button_new (name,
		                                                   id,
		                                                   settings_path,
		                                                   WACOM_TABLET_BUTTON_TYPE_NORMAL,
		                                                   gsd_wacom_device_button_pos (flags),
		                                                   flags_to_group (flags),
		                                                   -1,
		                                                   GSD_WACOM_NO_LED));
		g_free (name);
		g_free (id);
	}


	for (i = 'A'; i < 'A' + num_buttons; i++) {
		WacomButtonFlags flags;
		char *name, *id;
		int status_led;

		flags = libwacom_get_button_flag (wacom_device, i);
		if (!(flags & direction))
			continue;

		if (!(flags & WACOM_BUTTON_MODESWITCH))
			continue;

		name = gsd_wacom_device_modeswitch_name (flags, button_num++);
		id = g_strdup_printf ("%s%c", button_str_id, i);
		status_led = libwacom_get_button_led_group (wacom_device, i);
		l = g_list_append (l, gsd_wacom_tablet_button_new (name,
		                                                   id,
		                                                   settings_path,
		                                                   WACOM_TABLET_BUTTON_TYPE_HARDCODED,
		                                                   gsd_wacom_device_button_pos (flags),
		                                                   flags_to_group (flags),
		                                                   -1,
		                                                   status_led));
		g_free (name);
		g_free (id);
	}


	if (libwacom_has_ring2 (wacom_device) || libwacom_has_ring (wacom_device))
		l = g_list_concat (l, gsd_wacom_device_add_ring_modes (wacom_device, settings_path, direction));
	if  (libwacom_get_num_strips (wacom_device) > 0)
		l = g_list_concat (l, gsd_wacom_device_add_strip_modes (wacom_device, settings_path, direction));

	return l;
}
