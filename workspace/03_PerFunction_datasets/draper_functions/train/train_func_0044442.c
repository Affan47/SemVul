it87_gpio_direction_in(struct gpio_chip *chip, unsigned gpio_num)
{
	u8 mask, group;
	int rc = 0;
	struct it87_gpio *it87_gpio = to_it87_gpio(chip);

	mask = 1 << (gpio_num % 8);
	group = (gpio_num / 8);

	spin_lock(&it87_gpio->lock);

	rc = superio_enter();
	if (rc)
		goto exit;


	superio_clear_mask(mask, group + it87_gpio->output_base);

	superio_exit();

exit:
	spin_unlock(&it87_gpio->lock);
	return rc;
}
