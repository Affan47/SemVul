pwm_regulator_set_voltage(struct regulator_dev *rdev,
					int min_uV, int max_uV,
					unsigned *selector)
{
	struct pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);
	unsigned int ramp_delay = rdev->constraints->ramp_delay;
	unsigned int period = pwm_get_period(drvdata->pwm);
	int duty_cycle;
	int ret;

	duty_cycle = pwm_voltage_to_duty_cycle_percentage(rdev, min_uV);

	ret = pwm_config(drvdata->pwm, (period / 100) * duty_cycle, period);
	if (ret) {
		dev_err(&rdev->dev, "Failed to configure PWM\n");
		return ret;
	}

	ret = pwm_enable(drvdata->pwm);
	if (ret) {
		dev_err(&rdev->dev, "Failed to enable PWM\n");
		return ret;
	}
	drvdata->volt_uV = min_uV;


	usleep_range(ramp_delay, ramp_delay + 1000);

	return 0;
}
