btd_device_remove_attio_callback(struct btd_device *device, guint id)
{
	struct attio_data *attio;
	GSList *l;

	l = g_slist_find_custom(device->attios, GUINT_TO_POINTER(id),
								attio_id_cmp);
	if (l) {
		attio = l->data;
		device->attios = g_slist_remove(device->attios, attio);
	} else {
		l = g_slist_find_custom(device->attios_offline,
					GUINT_TO_POINTER(id), attio_id_cmp);
		if (!l)
			return FALSE;

		attio = l->data;
		device->attios_offline = g_slist_remove(device->attios_offline,
									attio);
	}

	g_free(attio);

	if (device->attios != NULL || device->attios_offline != NULL)
		return TRUE;

	if (device->auto_id) {
		g_source_remove(device->auto_id);
		device->auto_id = 0;
	}

	att_cleanup(device);

	return TRUE;
}
