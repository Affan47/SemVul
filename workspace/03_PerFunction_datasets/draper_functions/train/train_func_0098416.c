gsd_wacom_device_set_next_mode (GsdWacomDevice       *device,
				GsdWacomTabletButton *button)
{
	GList *l;
	int current_idx;
	int num_modes;
	int num_switches;
	int group_id;

	g_return_val_if_fail (GSD_IS_WACOM_DEVICE (device), -1);

	group_id = button->group_id;
	current_idx = 0;
	num_switches = 0;
	num_modes = GPOINTER_TO_INT (g_hash_table_lookup (device->priv->num_modes, GINT_TO_POINTER(group_id)));


	for (l = device->priv->buttons; l != NULL; l = l->next) {
		GsdWacomTabletButton *b = l->data;
		if (b->type != WACOM_TABLET_BUTTON_TYPE_HARDCODED)
			continue;
		if (button->group_id == b->group_id)
			num_switches++;
		if (g_strcmp0 (button->id, b->id) == 0)
			current_idx = num_switches;
	}


	g_return_val_if_fail (num_switches != 0, -1);


	if (num_switches == 1) {
		current_idx = gsd_wacom_device_get_current_mode (device, group_id);

		g_return_val_if_fail (current_idx > 0, -1);

		current_idx++;
	}

	if (current_idx > num_modes)
		current_idx = 1;

	g_hash_table_insert (device->priv->modes, GINT_TO_POINTER (group_id), GINT_TO_POINTER (current_idx));

	return current_idx;
}
