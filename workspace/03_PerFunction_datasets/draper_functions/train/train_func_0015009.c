lpc18xx_valid_pin_function(unsigned pin, unsigned function)
{
	struct lpc18xx_pin_caps *p = lpc18xx_pins[pin].drv_data;
	int i;

	if (function == FUNC_DAC && p->analog == DAC)
		return true;

	if (function == FUNC_ADC && p->analog)
		return true;

	if (function == FUNC_I2C0 && p->type == TYPE_I2C0)
		return true;

	if (function == FUNC_USB1 && p->type == TYPE_USB1)
		return true;

	for (i = 0; i < LPC18XX_SCU_FUNC_PER_PIN; i++) {
		if (function == p->functions[i])
			return true;
	}

	return false;
}
