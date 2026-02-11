atmel_hlcdc_pwm_set_polarity(struct pwm_chip *c,
					struct pwm_device *pwm,
					enum pwm_polarity polarity)
{
	struct atmel_hlcdc_pwm *chip = to_atmel_hlcdc_pwm(c);
	struct atmel_hlcdc *hlcdc = chip->hlcdc;
	u32 cfg = 0;

	if (polarity == PWM_POLARITY_NORMAL)
		cfg = ATMEL_HLCDC_PWMPOL;

	return regmap_update_bits(hlcdc->regmap, ATMEL_HLCDC_CFG(6),
				  ATMEL_HLCDC_PWMPOL, cfg);
}
