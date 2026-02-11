picolcd_init_backlight(struct picolcd_data *data, struct hid_report *report)
{
	struct device *dev = &data->hdev->dev;
	struct backlight_device *bdev;
	struct backlight_properties props;
	if (!report)
		return -ENODEV;
	if (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) {
		dev_err(dev, "unsupported BRIGHTNESS report");
		return -EINVAL;
	}

	memset(&props, 0, sizeof(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 0xff;
	bdev = backlight_device_register(dev_name(dev), dev, data,
			&picolcd_blops, &props);
	if (IS_ERR(bdev)) {
		dev_err(dev, "failed to register backlight\n");
		return PTR_ERR(bdev);
	}
	bdev->props.brightness     = 0xff;
	data->lcd_brightness       = 0xff;
	data->backlight            = bdev;
	picolcd_set_brightness(bdev);
	return 0;
}
