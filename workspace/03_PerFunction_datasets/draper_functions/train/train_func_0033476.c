modem_object_added (MMManager *modem_manager,
                    MMObject  *modem_object,
                    NmaBtDevice *self)
{
	NmaBtDevicePrivate *priv = NMA_BT_DEVICE_GET_PRIVATE (self);
	NMDeviceType devtype = NM_DEVICE_TYPE_UNKNOWN;
	MMModem *modem_iface;
	const gchar *path;
	const gchar *primary_port;
	const gchar *iface_basename;
	MMModemCapability caps;

	path = mm_object_get_path (modem_object);
	g_message ("%s: (%s) modem found", __func__, path);


	modem_iface = mm_object_peek_modem (modem_object);
	g_return_if_fail (modem_iface != NULL);


	primary_port = mm_modem_get_primary_port (modem_iface);
	g_return_if_fail (primary_port != NULL);


	iface_basename = g_path_get_basename (priv->rfcomm_iface);


	if (!g_str_equal (primary_port, iface_basename)) {
		g_message ("%s: (%s) (%s) not the modem we're looking for (%s)",
		           __func__, path, primary_port, iface_basename);
		return;
	}


	caps = mm_modem_get_current_capabilities (modem_iface);

	if (caps == MM_MODEM_CAPABILITY_CDMA_EVDO)
		devtype = NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO;

	else if (caps == MM_MODEM_CAPABILITY_GSM_UMTS)
		devtype = NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS;

	else if (caps & MM_MODEM_CAPABILITY_LTE)
		devtype = NM_DEVICE_MODEM_CAPABILITY_LTE;
	else
		g_message ("%s: (%s) unknown modem type", __func__, path);


	start_wizard (self, path, devtype);
}
