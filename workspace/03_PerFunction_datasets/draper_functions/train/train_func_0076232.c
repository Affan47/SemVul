cal_client_get_view_in_dbus_thread (GSimpleAsyncResult *simple,
                                    GObject *source_object,
                                    GCancellable *cancellable)
{
	ECalClient *client = E_CAL_CLIENT (source_object);
	AsyncContext *async_context;
	gchar *utf8_sexp;
	gchar *object_path = NULL;
	GError *local_error = NULL;

	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	utf8_sexp = e_util_utf8_make_valid (async_context->sexp);

	e_dbus_calendar_call_get_view_sync (
		client->priv->dbus_proxy, utf8_sexp,
		&object_path, cancellable, &local_error);

	g_free (utf8_sexp);


	g_return_if_fail (
		((object_path != NULL) && (local_error == NULL)) ||
		((object_path == NULL) && (local_error != NULL)));

	if (object_path != NULL) {
		GDBusConnection *connection;
		ECalClientView *client_view;

		connection = g_dbus_proxy_get_connection (
			G_DBUS_PROXY (client->priv->dbus_proxy));

		client_view = g_initable_new (
			E_TYPE_CAL_CLIENT_VIEW,
			cancellable, &local_error,
			"client", client,
			"connection", connection,
			"object-path", object_path,
			NULL);


		g_return_if_fail (
			((client_view != NULL) && (local_error == NULL)) ||
			((client_view == NULL) && (local_error != NULL)));

		async_context->client_view = client_view;

		g_free (object_path);
	}

	if (local_error != NULL) {
		g_dbus_error_strip_remote_error (local_error);
		g_simple_async_result_take_error (simple, local_error);
	}
}
