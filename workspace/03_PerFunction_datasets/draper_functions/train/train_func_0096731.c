cd_util_get_devices_by_kind (CdUtilPrivate *priv, gchar **values, GError **error)
{
	CdDevice *device;
	gboolean ret = TRUE;
	GPtrArray *array = NULL;
	guint i;

	if (g_strv_length (values) < 1) {
		ret = FALSE;
		g_set_error_literal (error,
				     1, 0,
				     "Not enough arguments, "
				     "expected device kind "
				     "e.g. 'printer'");
		goto out;
	}


	array = cd_client_get_devices_by_kind_sync (priv->client,
			cd_device_kind_from_string (values[0]),
			NULL,
			error);
	if (array == NULL) {
		ret = FALSE;
		goto out;
	}
	for (i = 0; i < array->len; i++) {
		device = g_ptr_array_index (array, i);
		ret = cd_device_connect_sync (device, NULL, error);
		if (!ret)
			goto out;
		cd_util_show_device (device);
		if (i != array->len - 1)
			g_print ("\n");
	}
out:
	if (array != NULL)
		g_ptr_array_unref (array);
	return ret;
}
