set_power_light_amber_noblink(void)
{
	struct nasgpio_led *amber = get_led_named("power:amber:power");
	struct nasgpio_led *blue = get_led_named("power:blue:power");

	if (!amber || !blue)
		return;


	pr_debug("setting blue off and amber on\n");

	nasgpio_led_set_brightness(&blue->led_cdev, LED_OFF);
	nasgpio_led_set_brightness(&amber->led_cdev, LED_FULL);
}
