nm_device_bring_up (NMDevice *self, gboolean block, gboolean *no_firmware)
{
	gboolean success = FALSE;

	g_return_val_if_fail (NM_IS_DEVICE (self), FALSE);

	if (!nm_device_hw_bring_up (self, block, no_firmware))
		return FALSE;

	if (nm_device_is_up (self))
		return TRUE;

	nm_log_info (LOGD_HW, "(%s): preparing device.", nm_device_get_iface (self));

	if (NM_DEVICE_GET_CLASS (self)->bring_up)
		success = NM_DEVICE_GET_CLASS (self)->bring_up (self);

	return success;
}
