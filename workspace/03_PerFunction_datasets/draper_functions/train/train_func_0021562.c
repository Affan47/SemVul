on_init_load_secret (GObject *source,
                     GAsyncResult *result,
                     gpointer user_data)
{
	GSimpleAsyncResult *async = G_SIMPLE_ASYNC_RESULT (user_data);
	SecretItem *self = SECRET_ITEM (source);
	GError *error = NULL;

	if (!secret_item_load_secret_finish (self, result, &error))
		g_simple_async_result_take_error (async, error);

	g_simple_async_result_complete (async);
	g_object_unref (async);
}
