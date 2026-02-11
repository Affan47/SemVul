gpiod_get_direction(struct gpio_desc *desc)
{
	struct gpio_chip	*chip;
	unsigned		offset;
	int			status = -EINVAL;

	chip = gpiod_to_chip(desc);
	offset = gpio_chip_hwgpio(desc);

	if (!chip->get_direction)
		return status;

	status = chip->get_direction(chip, offset);
	if (status > 0) {

		status = 1;
		clear_bit(FLAG_IS_OUT, &desc->flags);
	}
	if (status == 0) {

		set_bit(FLAG_IS_OUT, &desc->flags);
	}
	return status;
}
