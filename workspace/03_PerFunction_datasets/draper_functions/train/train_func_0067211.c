dln2_gpio_pin_get_out_val(struct dln2_gpio *dln2, unsigned int pin)
{
	int ret;

	ret = dln2_gpio_pin_val(dln2, DLN2_GPIO_PIN_GET_OUT_VAL, pin);
	if (ret < 0)
		return ret;
	return !!ret;
}
