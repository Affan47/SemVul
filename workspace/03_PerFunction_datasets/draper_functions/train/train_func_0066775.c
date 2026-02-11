up_device_refresh_sync (UpDevice *device, GCancellable *cancellable, GError **error)
{
	GError *error_local = NULL;
	gboolean ret;

	g_return_val_if_fail (UP_IS_DEVICE (device), FALSE);
	g_return_val_if_fail (device->priv->proxy_device != NULL, FALSE);


	ret = dbus_g_proxy_call (device->priv->proxy_device, "Refresh", &error_local,
				 G_TYPE_INVALID, G_TYPE_INVALID);
	if (!ret) {
		g_set_error (error, 1, 0, "Refresh() on %s failed: %s", device->priv->object_path, error_local->message);
		g_error_free (error_local);
		goto out;
	}
out:
	return ret;
}
