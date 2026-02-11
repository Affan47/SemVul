bluetooth_client_create_device (BluetoothClient *client,
					 const char *address,
					 const char *agent,
					 BluetoothClientCreateDeviceFunc func,
					 gpointer data)
{
	BluetoothClientPrivate *priv = BLUETOOTH_CLIENT_GET_PRIVATE(client);
	CreateDeviceData *devdata;
	GDBusProxy *adapter;
	GtkTreeIter iter;

	g_return_val_if_fail (BLUETOOTH_IS_CLIENT (client), FALSE);
	g_return_val_if_fail (address != NULL, FALSE);

	adapter = _bluetooth_client_get_default_adapter(client);
	if (adapter == NULL)
		return FALSE;


	if (agent != NULL &&
	    get_iter_from_address(priv->store, &iter, address, adapter) == TRUE) {
		GDBusProxy *device;
		gboolean paired;
		GError *err = NULL;

		gtk_tree_model_get (GTK_TREE_MODEL(priv->store), &iter,
				    BLUETOOTH_COLUMN_PROXY, &device,
				    BLUETOOTH_COLUMN_PAIRED, &paired, -1);
		if (device != NULL &&
		    paired != FALSE &&
		    adapter_call_remove_device_sync (ADAPTER (adapter),
		    				     g_dbus_proxy_get_object_path (device),
		    				     NULL, &err) == FALSE) {
			g_warning ("Failed to remove device '%s': %s", address,
				   err->message);
			g_error_free (err);
		}
		if (device != NULL)
			g_object_unref (device);
	}

	devdata = g_new0 (CreateDeviceData, 1);
	devdata->func = func;
	devdata->data = data;
	devdata->client = g_object_ref (client);

	if (agent != NULL)
		g_dbus_proxy_call (adapter,
				   "CreatePairedDevice",
				   g_variant_new ("(sos)", address, agent, "DisplayYesNo"),
				   G_DBUS_CALL_FLAGS_NONE,
				   90 * 1000,
				   NULL,
				   (GAsyncReadyCallback) create_device_callback,
				   devdata);
	else
		g_dbus_proxy_call (adapter,
				   "CreateDevice",
				   g_variant_new ("(s)", address),
				   G_DBUS_CALL_FLAGS_NONE,
				   90 * 1000,
				   NULL,
				   (GAsyncReadyCallback) create_device_callback,
				   devdata);
	g_object_unref (adapter);

	return TRUE;
}
