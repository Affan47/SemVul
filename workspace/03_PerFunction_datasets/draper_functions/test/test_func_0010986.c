max77693_haptic_enable(struct max77693_haptic *haptic)
{
	int error;

	if (haptic->enabled)
		return;

	error = pwm_enable(haptic->pwm_dev);
	if (error) {
		dev_err(haptic->dev,
			"failed to enable haptic pwm device: %d\n", error);
		return;
	}

	error = max77693_haptic_lowsys(haptic, true);
	if (error)
		goto err_enable_lowsys;

	error = max77693_haptic_configure(haptic, true);
	if (error)
		goto err_enable_config;

	haptic->enabled = true;

	return;

err_enable_config:
	max77693_haptic_lowsys(haptic, false);
err_enable_lowsys:
	pwm_disable(haptic->pwm_dev);
}
