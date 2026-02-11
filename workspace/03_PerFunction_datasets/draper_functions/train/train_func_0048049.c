pps_gpio_irq_handler(int irq, void *data)
{
	const struct pps_gpio_device_data *info;
	struct pps_event_time ts;
	int rising_edge;


	pps_get_ts(&ts);

	info = data;

	rising_edge = gpio_get_value(info->gpio_pin);
	if ((rising_edge && !info->assert_falling_edge) ||
			(!rising_edge && info->assert_falling_edge))
		pps_event(info->pps, &ts, PPS_CAPTUREASSERT, NULL);
	else if (info->capture_clear &&
			((rising_edge && info->assert_falling_edge) ||
			 (!rising_edge && !info->assert_falling_edge)))
		pps_event(info->pps, &ts, PPS_CAPTURECLEAR, NULL);

	return IRQ_HANDLED;
}
