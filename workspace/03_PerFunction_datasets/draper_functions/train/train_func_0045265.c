sun4i_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			    int duty_ns, int period_ns)
{
	struct sun4i_pwm_chip *sun4i_pwm = to_sun4i_pwm_chip(chip);
	u32 prd, dty, val, clk_gate;
	u64 clk_rate, div = 0;
	unsigned int prescaler = 0;
	int err;

	clk_rate = clk_get_rate(sun4i_pwm->clk);

	if (sun4i_pwm->data->has_prescaler_bypass) {

		prescaler = PWM_PRESCAL_MASK;


		div = clk_rate * period_ns + NSEC_PER_SEC / 2;
		do_div(div, NSEC_PER_SEC);
		if (div - 1 > PWM_PRD_MASK)
			prescaler = 0;
	}

	if (prescaler == 0) {

		for (prescaler = 0; prescaler < PWM_PRESCAL_MASK; prescaler++) {
			if (!prescaler_table[prescaler])
				continue;
			div = clk_rate;
			do_div(div, prescaler_table[prescaler]);
			div = div * period_ns;
			do_div(div, NSEC_PER_SEC);
			if (div - 1 <= PWM_PRD_MASK)
				break;
		}

		if (div - 1 > PWM_PRD_MASK) {
			dev_err(chip->dev, "period exceeds the maximum value\n");
			return -EINVAL;
		}
	}

	prd = div;
	div *= duty_ns;
	do_div(div, period_ns);
	dty = div;

	err = clk_prepare_enable(sun4i_pwm->clk);
	if (err) {
		dev_err(chip->dev, "failed to enable PWM clock\n");
		return err;
	}

	spin_lock(&sun4i_pwm->ctrl_lock);
	val = sun4i_pwm_readl(sun4i_pwm, PWM_CTRL_REG);

	if (sun4i_pwm->data->has_rdy && (val & PWM_RDY(pwm->hwpwm))) {
		spin_unlock(&sun4i_pwm->ctrl_lock);
		clk_disable_unprepare(sun4i_pwm->clk);
		return -EBUSY;
	}

	clk_gate = val & BIT_CH(PWM_CLK_GATING, pwm->hwpwm);
	if (clk_gate) {
		val &= ~BIT_CH(PWM_CLK_GATING, pwm->hwpwm);
		sun4i_pwm_writel(sun4i_pwm, val, PWM_CTRL_REG);
	}

	val = sun4i_pwm_readl(sun4i_pwm, PWM_CTRL_REG);
	val &= ~BIT_CH(PWM_PRESCAL_MASK, pwm->hwpwm);
	val |= BIT_CH(prescaler, pwm->hwpwm);
	sun4i_pwm_writel(sun4i_pwm, val, PWM_CTRL_REG);

	val = (dty & PWM_DTY_MASK) | PWM_PRD(prd);
	sun4i_pwm_writel(sun4i_pwm, val, PWM_CH_PRD(pwm->hwpwm));

	if (clk_gate) {
		val = sun4i_pwm_readl(sun4i_pwm, PWM_CTRL_REG);
		val |= clk_gate;
		sun4i_pwm_writel(sun4i_pwm, val, PWM_CTRL_REG);
	}

	spin_unlock(&sun4i_pwm->ctrl_lock);
	clk_disable_unprepare(sun4i_pwm->clk);

	return 0;
}
