toshiba_kbd_backlight_set(struct led_classdev *cdev,
				     enum led_brightness brightness)
{
	struct toshiba_acpi_dev *dev = container_of(cdev,
			struct toshiba_acpi_dev, kbd_led);
	u32 result;
	u32 state;


	state = brightness ? 1 : 0;
	result = hci_write(dev, HCI_KBD_ILLUMINATION, state);
	if (result == TOS_FAILURE)
		pr_err("ACPI call to set KBD Illumination mode failed\n");
}
