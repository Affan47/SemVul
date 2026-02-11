adp5520_gpio_get_value(struct gpio_chip *chip, unsigned off)
{
	struct adp5520_gpio *dev;
	uint8_t reg_val;

	dev = container_of(chip, struct adp5520_gpio, gpio_chip);


	if (test_bit(off, &dev->output))
		adp5520_read(dev->master, ADP5520_GPIO_OUT, &reg_val);
	else
		adp5520_read(dev->master, ADP5520_GPIO_IN, &reg_val);

	return !!(reg_val & dev->lut[off]);
}
