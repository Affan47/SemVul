toneport_init_leds(struct usb_line6_toneport *toneport)
{
	struct device *dev = &toneport->line6.usbdev->dev;
	int i, err;

	for (i = 0; i < 2; i++) {
		struct toneport_led *led = &toneport->leds[i];
		struct led_classdev *leddev = &led->dev;

		led->toneport = toneport;
		snprintf(led->name, sizeof(led->name), "%s::%s",
			 dev_name(dev), led_colors[i]);
		leddev->name = led->name;
		leddev->brightness = led_init_vals[i];
		leddev->max_brightness = 0x26;
		leddev->brightness_set = toneport_led_brightness_set;
		err = led_classdev_register(dev, leddev);
		if (err)
			return err;
		led->registered = true;
	}

	return 0;
}
