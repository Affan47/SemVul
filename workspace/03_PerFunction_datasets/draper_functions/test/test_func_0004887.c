cd_util_sensor_lock (CdUtilPrivate *priv, gchar **values, GError **error)
{
	CdSensor *sensor;
	gboolean ret = TRUE;
	GMainLoop *loop = NULL;
	GPtrArray *array = NULL;
	guint i;


	array = cd_client_get_sensors_sync (priv->client, NULL, error);
	if (array == NULL) {
		ret = FALSE;
		goto out;
	}
	if (array->len == 0) {
		ret = FALSE;

		g_set_error_literal (error, 1, 0,
				     _("There are no supported sensors attached"));
		goto out;
	}
	for (i = 0; i < array->len; i++) {
		sensor = g_ptr_array_index (array, i);

		ret = cd_sensor_connect_sync (sensor, NULL, error);
		if (!ret)
			goto out;


		ret = cd_sensor_lock_sync (sensor,
					   NULL,
					   error);
		if (!ret)
			goto out;
	}


	loop = g_main_loop_new (NULL, TRUE);
	g_main_loop_run (loop);
out:
	if (loop != NULL)
		g_main_loop_unref (loop);
	if (array != NULL)
		g_ptr_array_unref (array);
	return ret;
}
