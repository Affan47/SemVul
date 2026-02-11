WMID_set_u32(u32 value, u32 cap)
{
	u32 method_id = 0;
	char param;

	switch (cap) {
	case ACER_CAP_BRIGHTNESS:
		if (value > max_brightness)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_BRIGHTNESS_METHODID;
		break;
	case ACER_CAP_WIRELESS:
		if (value > 1)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_WIRELESS_METHODID;
		break;
	case ACER_CAP_BLUETOOTH:
		if (value > 1)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_BLUETOOTH_METHODID;
		break;
	case ACER_CAP_THREEG:
		if (value > 1)
			return AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_THREEG_METHODID;
		break;
	case ACER_CAP_MAILLED:
		if (value > 1)
			return AE_BAD_PARAMETER;
		if (quirks->mailled == 1) {
			param = value ? 0x92 : 0x93;
			i8042_lock_chip();
			i8042_command(&param, 0x1059);
			i8042_unlock_chip();
			return 0;
		}
		break;
	default:
		return AE_ERROR;
	}
	return WMI_execute_u32(method_id, (u32)value, NULL);
}
