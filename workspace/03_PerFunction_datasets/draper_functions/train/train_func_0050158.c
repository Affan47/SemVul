lenovo_probe_tpkbd(struct hid_device *hdev)
{
	struct device *dev = &hdev->dev;
	struct lenovo_drvdata_tpkbd *data_pointer;
	size_t name_sz = strlen(dev_name(dev)) + 16;
	char *name_mute, *name_micmute;
	int i;
	int ret;


	if (!hid_get_drvdata(hdev))
		return 0;

	hid_set_drvdata(hdev, NULL);


	for (i = 0; i < 4; i++) {
		if (!hid_validate_values(hdev, HID_FEATURE_REPORT, 4, i, 1))
			return -ENODEV;
	}
	if (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 3, 0, 2))
		return -ENODEV;

	ret = sysfs_create_group(&hdev->dev.kobj, &lenovo_attr_group_tpkbd);
	if (ret)
		hid_warn(hdev, "Could not create sysfs group: %d\n", ret);

	data_pointer = devm_kzalloc(&hdev->dev,
				    sizeof(struct lenovo_drvdata_tpkbd),
				    GFP_KERNEL);
	if (data_pointer == NULL) {
		hid_err(hdev, "Could not allocate memory for driver data\n");
		ret = -ENOMEM;
		goto err;
	}


	data_pointer->sensitivity = 0xa0;
	data_pointer->press_speed = 0x38;

	name_mute = devm_kzalloc(&hdev->dev, name_sz, GFP_KERNEL);
	name_micmute = devm_kzalloc(&hdev->dev, name_sz, GFP_KERNEL);
	if (name_mute == NULL || name_micmute == NULL) {
		hid_err(hdev, "Could not allocate memory for led data\n");
		ret = -ENOMEM;
		goto err;
	}
	snprintf(name_mute, name_sz, "%s:amber:mute", dev_name(dev));
	snprintf(name_micmute, name_sz, "%s:amber:micmute", dev_name(dev));

	hid_set_drvdata(hdev, data_pointer);

	data_pointer->led_mute.name = name_mute;
	data_pointer->led_mute.brightness_get = lenovo_led_brightness_get_tpkbd;
	data_pointer->led_mute.brightness_set = lenovo_led_brightness_set_tpkbd;
	data_pointer->led_mute.dev = dev;
	led_classdev_register(dev, &data_pointer->led_mute);

	data_pointer->led_micmute.name = name_micmute;
	data_pointer->led_micmute.brightness_get =
		lenovo_led_brightness_get_tpkbd;
	data_pointer->led_micmute.brightness_set =
		lenovo_led_brightness_set_tpkbd;
	data_pointer->led_micmute.dev = dev;
	led_classdev_register(dev, &data_pointer->led_micmute);

	lenovo_features_set_tpkbd(hdev);

	return 0;
err:
	sysfs_remove_group(&hdev->dev.kobj, &lenovo_attr_group_tpkbd);
	return ret;
}
