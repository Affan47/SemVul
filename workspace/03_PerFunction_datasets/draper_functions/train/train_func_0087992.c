client_combo_box_get_client_done_cb (GObject *source_object,
                                     GAsyncResult *result,
                                     gpointer user_data)
{
	EClient *client;
	GSimpleAsyncResult *simple;
	GError *error = NULL;

	simple = G_SIMPLE_ASYNC_RESULT (user_data);

	client = e_client_cache_get_client_finish (
		E_CLIENT_CACHE (source_object), result, &error);


	g_return_if_fail (
		((client != NULL) && (error == NULL)) ||
		((client == NULL) && (error != NULL)));

	if (client != NULL) {
		g_simple_async_result_set_op_res_gpointer (
			simple, g_object_ref (client),
			(GDestroyNotify) g_object_unref);
		g_object_unref (client);
	}

	if (error != NULL)
		g_simple_async_result_take_error (simple, error);

	g_simple_async_result_complete (simple);

	g_object_unref (simple);
}
