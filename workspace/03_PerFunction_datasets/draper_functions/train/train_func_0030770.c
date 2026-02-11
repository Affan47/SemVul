nm_client_check_connectivity_async (NMClient *client,
                                    GCancellable *cancellable,
                                    GAsyncReadyCallback callback,
                                    gpointer user_data)
{
	NMClientPrivate *priv;
	GSimpleAsyncResult *simple;
	CheckConnectivityData *ccd;

	g_return_if_fail (NM_IS_CLIENT (client));
	priv = NM_CLIENT_GET_PRIVATE (client);

	ccd = g_slice_new (CheckConnectivityData);
	ccd->client = client;

	simple = g_simple_async_result_new (G_OBJECT (client), callback, user_data,
	                                    nm_client_check_connectivity_async);
	g_simple_async_result_set_op_res_gpointer (simple, ccd, (GDestroyNotify) check_connectivity_data_free);

	if (cancellable) {
		ccd->cancellable = g_object_ref (cancellable);
		ccd->cancelled_id = g_signal_connect (cancellable, "cancelled",
		                                      G_CALLBACK (check_connectivity_cancelled_cb),
		                                      simple);
		g_simple_async_result_set_check_cancellable (simple, cancellable);
	}

	ccd->call = dbus_g_proxy_begin_call (priv->client_proxy, "CheckConnectivity",
	                                     check_connectivity_cb, simple, NULL,
	                                     G_TYPE_INVALID);
}
