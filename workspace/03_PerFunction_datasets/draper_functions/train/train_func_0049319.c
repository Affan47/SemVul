bluez_connect_cb (GDBusConnection *dbus_connection,
                  GAsyncResult *res,
                  gpointer user_data)
{
	GSimpleAsyncResult *result = G_SIMPLE_ASYNC_RESULT (user_data);
	GObject *result_object = g_async_result_get_source_object (G_ASYNC_RESULT (result));
	NMBluezDevice *self = NM_BLUEZ_DEVICE (result_object);
	NMBluezDevicePrivate *priv = NM_BLUEZ_DEVICE_GET_PRIVATE (self);
	GError *error = NULL;
	char *device;
	GVariant *variant;

	variant = g_dbus_connection_call_finish (dbus_connection, res, &error);

	if (!variant) {
		g_simple_async_result_take_error (result, error);
	} else {
		g_variant_get (variant, "(s)", &device);

		g_simple_async_result_set_op_res_gpointer (result,
		                                           g_strdup (device),
		                                           g_free);
		priv->bt_iface = device;
		g_variant_unref (variant);
	}

	g_simple_async_result_complete (result);
	g_object_unref (result);
	g_object_unref (result_object);
}
