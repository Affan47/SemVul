dun_cleanup (NmaBtDevice *self)
{
	NmaBtDevicePrivate *priv = NMA_BT_DEVICE_GET_PRIVATE (self);
	GSList *iter;


	for (iter = priv->modem_proxies; iter; iter = g_slist_next (iter))
		g_object_unref (DBUS_G_PROXY (iter->data));
	g_slist_free (priv->modem_proxies);
	priv->modem_proxies = NULL;
	g_clear_object (&priv->mm_proxy);

#if WITH_MODEM_MANAGER_1
	g_clear_object (&priv->dbus_connection);
	g_clear_object (&priv->modem_manager_1);
#endif

	if (priv->dun_proxy && priv->rfcomm_iface) {
		dbus_g_proxy_call_no_reply (priv->dun_proxy, "Disconnect",
		                            G_TYPE_STRING, priv->rfcomm_iface,
		                            G_TYPE_INVALID);
	}
	g_clear_object (&priv->dun_proxy);

	g_free (priv->rfcomm_iface);
	priv->rfcomm_iface = NULL;

	if (priv->dun_timeout_id) {
		g_source_remove (priv->dun_timeout_id);
		priv->dun_timeout_id = 0;
	}

	if (priv->wizard) {
		nma_mobile_wizard_destroy (priv->wizard);
		priv->wizard = NULL;
	}
}
