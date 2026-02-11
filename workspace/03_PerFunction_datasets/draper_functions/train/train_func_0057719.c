dhcp4_fail (NMDevice *device, gboolean timeout)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (device);

	nm_dhcp4_config_reset (priv->dhcp4_config);

	if (timeout || (priv->ip4_state == IP_CONF))
		nm_device_activate_schedule_ip4_config_timeout (device);
	else if (priv->ip4_state == IP_DONE)
		nm_device_state_changed (device, NM_DEVICE_STATE_FAILED, NM_DEVICE_STATE_REASON_IP_CONFIG_EXPIRED);
}
