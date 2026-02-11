fsl_pwm_set_polarity(struct pwm_chip *chip,
				struct pwm_device *pwm,
				enum pwm_polarity polarity)
{
	struct fsl_pwm_chip *fpc = to_fsl_chip(chip);
	u32 val;

	regmap_read(fpc->regmap, FTM_POL, &val);

	if (polarity == PWM_POLARITY_INVERSED)
		val |= BIT(pwm->hwpwm);
	else
		val &= ~BIT(pwm->hwpwm);

	regmap_write(fpc->regmap, FTM_POL, val);

	return 0;
}
