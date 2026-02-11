sony_nc_update_status_ng(struct backlight_device *bd)
{
	int value, result;
	struct sony_backlight_props *sdev =
		(struct sony_backlight_props *)bl_get_data(bd);

	value = bd->props.brightness + sdev->offset;
	if (sony_call_snc_handle(sdev->handle, sdev->cmd_base | (value << 0x10),
				&result))
		return -EIO;

	return value;
}
