gpiod_get_raw_value(const struct gpio_desc *desc)
{
	if (!desc)
		return 0;

	WARN_ON(desc->chip->can_sleep);
	return _gpiod_get_raw_value(desc);
}
