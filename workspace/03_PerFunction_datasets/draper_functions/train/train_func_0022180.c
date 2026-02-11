get_tablet_button_label_touch  (GsdWacomDevice       *device,
				GsdWacomTabletButton *button,
				GtkDirectionType      dir)
{
	char **strv, *name, *str;

	strv = g_settings_get_strv (button->settings, CUSTOM_ELEVATOR_ACTION_KEY);
	name = NULL;

	if (strv) {
		if (g_strv_length (strv) >= 1 && dir == GTK_DIR_UP)
			name = g_strdup (strv[0]);
		else if (g_strv_length (strv) >= 2 && dir == GTK_DIR_DOWN)
			name = g_strdup (strv[1]);
		g_strfreev (strv);
	}

	str = get_escaped_accel_shortcut (name);
	g_free (name);
	name = str;


	if (gsd_wacom_device_get_num_modes (device, button->group_id) > 1) {
		name = g_strdup_printf (_("Mode %d: %s"), button->idx + 1, str);
		g_free (str);
	}

	return name;
}
