sony_nc_backlight_setup(void)
{
	int max_brightness = 0;
	const struct backlight_ops *ops = NULL;
	struct backlight_properties props;

	if (sony_find_snc_handle(0x12f) >= 0) {
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x0100;
		sony_nc_backlight_ng_read_limits(0x12f, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	} else if (sony_find_snc_handle(0x137) >= 0) {
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x0100;
		sony_nc_backlight_ng_read_limits(0x137, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	} else if (sony_find_snc_handle(0x143) >= 0) {
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x3000;
		sony_nc_backlight_ng_read_limits(0x143, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	} else if (sony_find_snc_handle(0x14b) >= 0) {
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x3000;
		sony_nc_backlight_ng_read_limits(0x14b, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	} else if (sony_find_snc_handle(0x14c) >= 0) {
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x3000;
		sony_nc_backlight_ng_read_limits(0x14c, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	} else if (acpi_has_method(sony_nc_acpi_handle, "GBRT")) {
		ops = &sony_backlight_ops;
		max_brightness = SONY_MAX_BRIGHTNESS - 1;

	} else
		return;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = max_brightness;
	sony_bl_props.dev = backlight_device_register("sony", NULL,
						      &sony_bl_props,
						      ops, &props);

	if (IS_ERR(sony_bl_props.dev)) {
		pr_warn("unable to register backlight device\n");
		sony_bl_props.dev = NULL;
	} else
		sony_bl_props.dev->props.brightness =
			ops->get_brightness(sony_bl_props.dev);
}
