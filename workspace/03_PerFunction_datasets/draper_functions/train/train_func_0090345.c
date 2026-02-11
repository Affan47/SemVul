hw_bring_up (NMDevice *device, gboolean *no_firmware)
{
	if (!NM_DEVICE_WIFI_GET_PRIVATE (device)->enabled)
		return FALSE;

	return NM_DEVICE_CLASS (nm_device_wifi_parent_class)->hw_bring_up (device, no_firmware);
}
