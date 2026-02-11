cd_sensor_connect_finish (CdSensor *sensor,
			  GAsyncResult *res,
			  GError **error)
{
	gpointer source_tag;
	GSimpleAsyncResult *simple;

	g_return_val_if_fail (CD_IS_SENSOR (sensor), FALSE);
	g_return_val_if_fail (G_IS_SIMPLE_ASYNC_RESULT (res), FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	simple = G_SIMPLE_ASYNC_RESULT (res);
	source_tag = g_simple_async_result_get_source_tag (simple);

	g_return_val_if_fail (source_tag == cd_sensor_connect, FALSE);

	if (g_simple_async_result_propagate_error (simple, error))
		return FALSE;

	return TRUE;
}
