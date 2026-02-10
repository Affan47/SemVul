e_gdbus_async_call_opid_ready_cb (GObject *source_proxy,
                                  GAsyncResult *result,
                                  gpointer user_data)
{
	GVariant *_result;
	GError *error = NULL;
	AsyncOpData *op_data = user_data;

	_result = g_dbus_proxy_call_finish (G_DBUS_PROXY (source_proxy), result, &error);

	if (_result != NULL && !error) {
		EGdbusAsyncOpKeeper *op_keeper = E_GDBUS_ASYNC_OP_KEEPER (source_proxy);
		GHashTable *pending_ops;
		gboolean add_pending = TRUE;

		g_return_if_fail (op_keeper != NULL);

		pending_ops = e_gdbus_async_op_keeper_get_pending_ops (op_keeper);
		g_return_if_fail (pending_ops != NULL);

		g_variant_get (_result, "(u)", &op_data->opid);
		g_variant_unref (_result);

		if (op_data->cancellable && !g_cancellable_set_error_if_cancelled (op_data->cancellable, &error))
			op_data->cancel_id = g_cancellable_connect (op_data->cancellable, G_CALLBACK (e_gdbus_op_cancelled_cb), op_data, NULL);
		else
			add_pending = op_data->cancellable == NULL;


		if (add_pending)
			g_hash_table_insert (pending_ops, GUINT_TO_POINTER (op_data->opid), op_data);
	} else if (_result) {
		g_variant_unref (_result);
	}

	if (error) {
		async_op_complete (op_data, error, FALSE);
		g_error_free (error);
	}
}
