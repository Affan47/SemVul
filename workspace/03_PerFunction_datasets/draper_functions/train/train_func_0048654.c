deactivate (NMModem *modem, NMDevice *device)
{
	NMModemGsmPrivate *priv = NM_MODEM_GSM_GET_PRIVATE (modem);

	if (priv->call) {
		DBusGProxy *proxy;

		proxy = nm_modem_generic_get_proxy (NM_MODEM_GENERIC (modem), MM_OLD_DBUS_INTERFACE_MODEM_SIMPLE);
		dbus_g_proxy_cancel_call (proxy, priv->call);
		priv->call = NULL;
	}

	priv->pin_tries = 0;

	if (priv->enable_delay_id)
		g_source_remove (priv->enable_delay_id);

	NM_MODEM_CLASS (nm_modem_gsm_parent_class)->deactivate (modem, device);
}
