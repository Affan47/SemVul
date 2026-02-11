remove_supplicant_connection_timeout (NMDeviceWifi *self)
{
	NMDeviceWifiPrivate *priv;

	g_return_if_fail (self != NULL);
	priv = NM_DEVICE_WIFI_GET_PRIVATE (self);


	if (priv->supplicant.con_timeout_id) {
		g_source_remove (priv->supplicant.con_timeout_id);
		priv->supplicant.con_timeout_id = 0;
	}
}
