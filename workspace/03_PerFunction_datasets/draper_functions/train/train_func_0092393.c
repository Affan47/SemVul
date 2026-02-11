brasero_io_return_result (const BraseroIOJobBase *base,
			  const gchar *uri,
			  GFileInfo *info,
			  GError *error,
			  BraseroIOResultCallbackData *callback_data)
{
	BraseroIO *self = brasero_io_get_default ();
	BraseroIOJobResult *result;


	result = g_new0 (BraseroIOJobResult, 1);
	result->base = base;
	result->info = info;
	result->error = error;
	result->uri = g_strdup (uri);

	if (callback_data) {
		g_atomic_int_inc (&callback_data->ref);
		result->callback_data = callback_data;
	}

	brasero_io_queue_result (self, result);
	g_object_unref (self);
}
