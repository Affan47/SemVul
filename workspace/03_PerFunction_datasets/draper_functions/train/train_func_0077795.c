twl4030_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct twl_pwm_chip *twl = to_twl(chip);
	int ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_read_u8(TWL4030_MODULE_INTBR, &val, TWL4030_GPBR1_REG);
	if (ret < 0) {
		dev_err(chip->dev, "%s: Failed to read GPBR1\n", pwm->label);
		goto out;
	}

	val &= ~TWL4030_PWM_TOGGLE(pwm->hwpwm, TWL4030_PWMX_ENABLE);

	ret = twl_i2c_write_u8(TWL4030_MODULE_INTBR, val, TWL4030_GPBR1_REG);
	if (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);

	val &= ~TWL4030_PWM_TOGGLE(pwm->hwpwm, TWL4030_PWMXCLK_ENABLE);

	ret = twl_i2c_write_u8(TWL4030_MODULE_INTBR, val, TWL4030_GPBR1_REG);
	if (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
}
