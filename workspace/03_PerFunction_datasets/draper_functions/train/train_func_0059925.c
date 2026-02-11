smscore_led_state(struct smscore_device_t *core, int led)
{
	if (led >= 0)
		core->led_state = led;
	return core->led_state;
}
