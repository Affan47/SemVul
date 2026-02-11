max732x_gpio_get_value(struct gpio_chip *gc, unsigned off)
{
	struct max732x_chip *chip = to_max732x(gc);
	uint8_t reg_val;
	int ret;

	ret = max732x_readb(chip, is_group_a(chip, off), &reg_val);
	if (ret < 0)
		return 0;

	return reg_val & (1u << (off & 0x7));
}
