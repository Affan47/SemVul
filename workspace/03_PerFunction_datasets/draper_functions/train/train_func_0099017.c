nasgpio_led_get_attr(struct led_classdev *led_cdev, u32 port)
{
	struct nasgpio_led *led = led_classdev_to_nasgpio_led(led_cdev);
	u32 gpio_in;

	spin_lock(&nasgpio_gpio_lock);
	gpio_in = inl(nas_gpio_io_base + port);
	spin_unlock(&nasgpio_gpio_lock);
	if (gpio_in & (1<<led->gpio_bit))
		return 1;
	return 0;
}
