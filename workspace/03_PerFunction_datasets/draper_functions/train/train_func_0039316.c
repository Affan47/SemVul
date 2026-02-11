update_initial_hw_address (NMDevice *dev)
{
	NMDeviceWifi *self = NM_DEVICE_WIFI (dev);
	NMDeviceWifiPrivate *priv = NM_DEVICE_WIFI_GET_PRIVATE (self);
	char *mac_str = NULL;
	guint8 *addr = priv->initial_hw_addr;
	guint8 zero[ETH_ALEN] = {0,0,0,0,0,0};


	if (!memcmp (&priv->hw_addr, &zero, ETH_ALEN))
		update_hw_address (dev);

	if (memcmp (&priv->initial_hw_addr, &priv->hw_addr, ETH_ALEN))
		memcpy (&priv->initial_hw_addr, &priv->hw_addr, ETH_ALEN);

	mac_str = g_strdup_printf ("%02X:%02X:%02X:%02X:%02X:%02X",
	                           addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	nm_log_dbg (LOGD_DEVICE | LOGD_ETHER, "(%s): read initial MAC address %s",
	            nm_device_get_iface (dev), mac_str);

	g_free (mac_str);
}
