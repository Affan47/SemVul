gsd_wacom_device_add_ring_modes (WacomDevice      *wacom_device,
				 const char       *settings_path,
				 WacomButtonFlags  direction)
{
	GList *l;
	guint num_modes;
	guint group;
	guint i;
	char *name, *id;

	l = NULL;

	if ((direction & WACOM_BUTTON_POSITION_LEFT) && libwacom_has_ring (wacom_device)) {
		num_modes = libwacom_get_ring_num_modes (wacom_device);
		group = flags_to_group (WACOM_BUTTON_RING_MODESWITCH);
		if (num_modes == 0) {

			l = g_list_append (l, gsd_wacom_tablet_button_new (_("Left Ring"),
									   "left-ring-mode-1",
									   settings_path,
									   WACOM_TABLET_BUTTON_TYPE_RING,
									   WACOM_TABLET_BUTTON_POS_LEFT,
									   group,
									   0,
									   GSD_WACOM_NO_LED));
		} else {
			for (i = 1; i <= num_modes; i++) {
				name = g_strdup_printf (_("Left Ring Mode #%d"), i);
				id = g_strdup_printf ("left-ring-mode-%d", i);
				l = g_list_append (l, gsd_wacom_tablet_button_new (name,
				                                                   id,
				                                                   settings_path,
				                                                   WACOM_TABLET_BUTTON_TYPE_RING,
										   WACOM_TABLET_BUTTON_POS_LEFT,
				                                                   group,
				                                                   i - 1,
										   GSD_WACOM_NO_LED));
				g_free (name);
				g_free (id);
			}
		}
	} else if ((direction & WACOM_BUTTON_POSITION_RIGHT) && libwacom_has_ring2 (wacom_device)) {
		num_modes = libwacom_get_ring2_num_modes (wacom_device);
		group = flags_to_group (WACOM_BUTTON_RING2_MODESWITCH);
		if (num_modes == 0) {

			l = g_list_append (l, gsd_wacom_tablet_button_new (_("Right Ring"),
									   "right-ring-mode-1",
									   settings_path,
									   WACOM_TABLET_BUTTON_TYPE_RING,
									   WACOM_TABLET_BUTTON_POS_RIGHT,
									   group,
									   0,
									   GSD_WACOM_NO_LED));
		} else {
			for (i = 1; i <= num_modes; i++) {
				name = g_strdup_printf (_("Right Ring Mode #%d"), i);
				id = g_strdup_printf ("right-ring-mode-%d", i);
				l = g_list_append (l, gsd_wacom_tablet_button_new (name,
				                                                   id,
				                                                   settings_path,
				                                                   WACOM_TABLET_BUTTON_TYPE_RING,
										   WACOM_TABLET_BUTTON_POS_RIGHT,
				                                                   group,
				                                                   i - 1,
										   GSD_WACOM_NO_LED));
				g_free (name);
				g_free (id);
			}
		}
	}

	return l;
}
