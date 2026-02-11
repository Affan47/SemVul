fw_add_to_zone_cb (GError *error, gpointer user_data)
{
	NMDevice *self = NM_DEVICE (user_data);
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);

	priv->fw_call = NULL;

	if (error) {

	}

	activation_source_schedule (self, nm_device_activate_stage3_ip_config_start, 0);

	nm_log_info (LOGD_DEVICE, "Activation (%s) Stage 3 of 5 (IP Configure Start) scheduled.",
	             nm_device_get_iface (self));
}
