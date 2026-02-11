adapter_initialized (NMBluezAdapter *adapter, gboolean success, gpointer user_data)
{
	NMBluezManager *self = NM_BLUEZ_MANAGER (user_data);
	NMBluezManagerPrivate *priv = NM_BLUEZ_MANAGER_GET_PRIVATE (self);

	if (success) {
		GSList *devices, *iter;

		devices = nm_bluez_adapter_get_devices (adapter);
		for (iter = devices; iter; iter = g_slist_next (iter))
			emit_bdaddr_added (self, NM_BLUEZ_DEVICE (iter->data));
		g_slist_free (devices);

		g_signal_connect (adapter, "device-added", G_CALLBACK (device_added), self);
		g_signal_connect (adapter, "device-removed", G_CALLBACK (device_removed), self);
	} else {
		g_object_unref (priv->adapter);
		priv->adapter = NULL;
	}
}
