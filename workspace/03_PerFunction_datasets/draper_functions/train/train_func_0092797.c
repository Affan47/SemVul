oaktrail_backlight_init(void)
{
	struct backlight_device *bd;
	struct backlight_properties props;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = OT_EC_BL_BRIGHTNESS_MAX;
	bd = backlight_device_register(DRIVER_NAME,
				       &oaktrail_device->dev, NULL,
				       &oaktrail_bl_ops,
				       &props);

	if (IS_ERR(bd)) {
		oaktrail_bl_device = NULL;
		pr_warning("Unable to register backlight device\n");
		return PTR_ERR(bd);
	}

	oaktrail_bl_device = bd;

	bd->props.brightness = get_backlight_brightness(bd);
	bd->props.power = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	return 0;
}
