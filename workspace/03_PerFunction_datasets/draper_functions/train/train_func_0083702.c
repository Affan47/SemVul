pwm_disable(struct pwm_device *pwm)
{
	if (pwm && test_and_clear_bit(PWMF_ENABLED, &pwm->flags))
		pwm->chip->ops->disable(pwm->chip, pwm);
}
