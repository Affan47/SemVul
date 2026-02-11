steelseries_srws1_led_get_brightness(struct led_classdev *led_cdev)
{
	struct device *dev = led_cdev->dev->parent;
	struct hid_device *hid = container_of(dev, struct hid_device, dev);
	struct steelseries_srws1_data *drv_data;
	int i, value = 0;

	drv_data = hid_get_drvdata(hid);

	if (!drv_data) {
		hid_err(hid, "Device data not found.");
		return LED_OFF;
	}

	for (i = 0; i < SRWS1_NUMBER_LEDS; i++)
		if (led_cdev == drv_data->led[i]) {
			value = (drv_data->led_state >> i) & 1;
			break;
		}

	return value ? LED_FULL : LED_OFF;
}
