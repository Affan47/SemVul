vprbrd_gpiob_direction_output(struct gpio_chip *chip,
			unsigned offset, int value)
{
	int ret;
	struct vprbrd_gpio *gpio =
			container_of(chip, struct vprbrd_gpio, gpiob);
	struct vprbrd *vb = gpio->vb;

	gpio->gpiob_out |= (1 << offset);

	mutex_lock(&vb->lock);

	ret = vprbrd_gpiob_setdir(vb, offset, 1);
	if (ret)
		dev_err(chip->dev, "usb error setting pin to output\n");

	mutex_unlock(&vb->lock);

	vprbrd_gpiob_set(chip, offset, value);

	return ret;
}
