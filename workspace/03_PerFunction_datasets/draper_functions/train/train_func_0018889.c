supplicant_iface_connection_error_cb (NMSupplicantInterface *iface,
                                      const char *name,
                                      const char *message,
                                      gpointer user_data)
{
	NMDeviceEthernet *self = NM_DEVICE_ETHERNET (user_data);
	NMDeviceEthernetPrivate *priv = NM_DEVICE_ETHERNET_GET_PRIVATE (self);
	guint id;

	nm_log_warn (LOGD_DEVICE | LOGD_ETHER,
	             "Activation (%s/wired): association request to the supplicant failed: %s - %s",
	             nm_device_get_iface (NM_DEVICE (self)), name, message);

	if (priv->supplicant.iface_con_error_cb_id)
		g_source_remove (priv->supplicant.iface_con_error_cb_id);

	id = g_idle_add (supplicant_iface_connection_error_cb_handler, self);
	priv->supplicant.iface_con_error_cb_id = id;
}
