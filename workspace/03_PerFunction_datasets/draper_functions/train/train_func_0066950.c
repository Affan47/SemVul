update_led_state(struct libevdev *dev, const struct input_event *e)
{
	if (!libevdev_has_event_type(dev, EV_LED))
		return 1;

	if (e->code > LED_MAX)
		return 1;

	set_bit_state(dev->led_values, e->code, e->value != 0);

	return 0;
}
