request_gpios_match(struct fbtft_par *par, const struct fbtft_gpio *gpio)
{
	dev_dbg(par->info->device,
		"%s('%s')\n", __func__, gpio->name);

	if (strcasecmp(gpio->name, "wr") == 0) {

		par->EPIN = gpio->gpio;
		return GPIOF_OUT_INIT_LOW;
	} else if (strcasecmp(gpio->name, "cs0") == 0) {

		par->CS0 = gpio->gpio;
		return GPIOF_OUT_INIT_HIGH;
	} else if (strcasecmp(gpio->name, "cs1") == 0) {

		par->CS1 = gpio->gpio;
		return GPIOF_OUT_INIT_HIGH;
	}


	else if (strcasecmp(gpio->name, "rw") == 0) {
		par->RW = gpio->gpio;
		return GPIOF_OUT_INIT_LOW;
	}

	return FBTFT_GPIO_NO_MATCH;
}
