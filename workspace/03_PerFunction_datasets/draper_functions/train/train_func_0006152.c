picolcd_init_leds(struct picolcd_data *data, struct hid_report *report)
{
	struct device *dev = &data->hdev->dev;
	struct led_classdev *led;
	size_t name_sz = strlen(dev_name(dev)) + 8;
	char *name;
	int i, ret = 0;

	if (!report)
		return -ENODEV;
	if (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) {
		dev_err(dev, "unsupported LED_STATE report");
		return -EINVAL;
	}

	for (i = 0; i < 8; i++) {
		led = kzalloc(sizeof(struct led_classdev)+name_sz, GFP_KERNEL);
		if (!led) {
			dev_err(dev, "can't allocate memory for LED %d\n", i);
			ret = -ENOMEM;
			goto err;
		}
		name = (void *)(&led[1]);
		snprintf(name, name_sz, "%s::GPO%d", dev_name(dev), i);
		led->name = name;
		led->brightness = 0;
		led->max_brightness = 1;
		led->brightness_get = picolcd_led_get_brightness;
		led->brightness_set = picolcd_led_set_brightness;

		data->led[i] = led;
		ret = led_classdev_register(dev, data->led[i]);
		if (ret) {
			data->led[i] = NULL;
			kfree(led);
			dev_err(dev, "can't register LED %d\n", i);
			goto err;
		}
	}
	return 0;
err:
	for (i = 0; i < 8; i++)
		if (data->led[i]) {
			led = data->led[i];
			data->led[i] = NULL;
			led_classdev_unregister(led);
			kfree(led);
		}
	return ret;
}
