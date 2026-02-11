gpiod_cansleep(const struct gpio_desc *desc)
{
	if (!desc)
		return 0;
	return desc->chip->can_sleep;
}
