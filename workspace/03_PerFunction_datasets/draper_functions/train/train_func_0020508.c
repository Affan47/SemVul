tps65912_gpio_set(struct gpio_chip *gc, unsigned offset,
			      int value)
{
	struct tps65912_gpio_data *tps65912_gpio = to_tgd(gc);
	struct tps65912 *tps65912 = tps65912_gpio->tps65912;

	if (value)
		tps65912_set_bits(tps65912, TPS65912_GPIO1 + offset,
							GPIO_SET_MASK);
	else
		tps65912_clear_bits(tps65912, TPS65912_GPIO1 + offset,
								GPIO_SET_MASK);
}
