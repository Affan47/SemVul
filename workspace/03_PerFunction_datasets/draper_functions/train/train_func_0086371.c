dell_led_exit(void)
{
	int error = 0;

	if (wmi_has_guid(DELL_LED_BIOS_GUID)) {
		error = led_off();
		if (error == 0)
			led_classdev_unregister(&dell_led);
	}
}
