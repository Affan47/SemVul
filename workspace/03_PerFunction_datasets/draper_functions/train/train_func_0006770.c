ad7879_gpio_set_value(struct gpio_chip *chip,
				  unsigned gpio, int value)
{
	struct ad7879 *ts = container_of(chip, struct ad7879, gc);

	mutex_lock(&ts->mutex);
	if (value)
		ts->cmd_crtl2 |= AD7879_GPIO_DATA;
	else
		ts->cmd_crtl2 &= ~AD7879_GPIO_DATA;

	ad7879_write(ts, AD7879_REG_CTRL2, ts->cmd_crtl2);
	mutex_unlock(&ts->mutex);
}
