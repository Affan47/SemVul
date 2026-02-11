cx231xx_gpio_set(struct cx231xx *dev, struct cx231xx_reg_seq *gpio)
{
	int rc = 0;

	if (!gpio)
		return rc;


	while (gpio->sleep >= 0) {
		rc = cx231xx_set_gpio_value(dev, gpio->bit, gpio->val);
		if (rc < 0)
			return rc;

		if (gpio->sleep > 0)
			msleep(gpio->sleep);

		gpio++;
	}
	return rc;
}
