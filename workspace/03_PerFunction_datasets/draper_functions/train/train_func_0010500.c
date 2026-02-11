rc5t583_gpio_dir_output(struct gpio_chip *gc, unsigned offset,
			int value)
{
	struct rc5t583_gpio *rc5t583_gpio = to_rc5t583_gpio(gc);
	struct device *parent = rc5t583_gpio->rc5t583->dev;
	int ret;

	rc5t583_gpio_set(gc, offset, value);
	ret = rc5t583_set_bits(parent, RC5T583_GPIO_IOSEL, BIT(offset));
	if (ret < 0)
		return ret;


	return rc5t583_clear_bits(parent, RC5T583_GPIO_PGSEL, BIT(offset));
}
