e_ews_oof_settings_new_finish (GAsyncResult *result,
                               GError **error)
{
	GObject *source_object;
	GObject *object;

	g_return_val_if_fail (G_IS_ASYNC_RESULT (result), NULL);

	source_object = g_async_result_get_source_object (result);
	g_return_val_if_fail (source_object != NULL, NULL);

	object = g_async_initable_new_finish (
		G_ASYNC_INITABLE (source_object), result, error);

	g_object_unref (source_object);

	return (object != NULL) ? E_EWS_OOF_SETTINGS (object) : NULL;
}
