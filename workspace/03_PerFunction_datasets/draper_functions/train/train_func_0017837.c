kbd_led_init(struct device *dev)
{
	kbd_init();
	if (!kbd_led_present)
		return -ENODEV;
	if (!kbd_als_supported)
		kbd_led_groups[1] = NULL;
	kbd_led.max_brightness = kbd_get_max_level();
	if (!kbd_led.max_brightness) {
		kbd_led.max_brightness = kbd_get_valid_token_counts();
		if (kbd_led.max_brightness)
			kbd_led.max_brightness--;
	}
	return led_classdev_register(dev, &kbd_led);
}
