nm_udev_manager_query_devices (NMUdevManager *self)
{
	NMUdevManagerPrivate *priv = NM_UDEV_MANAGER_GET_PRIVATE (self);
	GList *devices, *iter;

	g_return_if_fail (self != NULL);
	g_return_if_fail (NM_IS_UDEV_MANAGER (self));

	devices = g_udev_client_query_by_subsystem (priv->client, "net");
	for (iter = devices; iter; iter = g_list_next (iter)) {
		net_add (self, G_UDEV_DEVICE (iter->data));
		g_object_unref (G_UDEV_DEVICE (iter->data));
	}
	g_list_free (devices);


	devices = g_udev_client_query_by_subsystem (priv->client, "atm");
	for (iter = devices; iter; iter = g_list_next (iter)) {
		adsl_add (self, G_UDEV_DEVICE (iter->data));
		g_object_unref (G_UDEV_DEVICE (iter->data));
	}
	g_list_free (devices);
}
