wacom_initialize_leds(struct wacom *wacom)
{
	int error;

	if (!(wacom->wacom_wac.features.device_type & WACOM_DEVICETYPE_PAD))
		return 0;


	switch (wacom->wacom_wac.features.type) {
	case INTUOS4S:
	case INTUOS4:
	case INTUOS4WL:
	case INTUOS4L:
		wacom->led.select[0] = 0;
		wacom->led.select[1] = 0;
		wacom->led.llv = 10;
		wacom->led.hlv = 20;
		wacom->led.img_lum = 10;
		error = sysfs_create_group(&wacom->hdev->dev.kobj,
					   &intuos4_led_attr_group);
		break;

	case WACOM_24HD:
	case WACOM_21UX2:
		wacom->led.select[0] = 0;
		wacom->led.select[1] = 0;
		wacom->led.llv = 0;
		wacom->led.hlv = 0;
		wacom->led.img_lum = 0;

		error = sysfs_create_group(&wacom->hdev->dev.kobj,
					   &cintiq_led_attr_group);
		break;

	case INTUOS5S:
	case INTUOS5:
	case INTUOS5L:
	case INTUOSPS:
	case INTUOSPM:
	case INTUOSPL:
		wacom->led.select[0] = 0;
		wacom->led.select[1] = 0;
		wacom->led.llv = 32;
		wacom->led.hlv = 0;
		wacom->led.img_lum = 0;

		error = sysfs_create_group(&wacom->hdev->dev.kobj,
					  &intuos5_led_attr_group);
		break;

	default:
		return 0;
	}

	if (error) {
		hid_err(wacom->hdev,
			"cannot create sysfs group err: %d\n", error);
		return error;
	}
	wacom_led_control(wacom);
	wacom->led_initialized = true;

	return 0;
}
