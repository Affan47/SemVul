max77693_haptic_play_work(struct work_struct *work)
{
	struct max77693_haptic *haptic =
			container_of(work, struct max77693_haptic, work);
	int error;

	error = max77693_haptic_set_duty_cycle(haptic);
	if (error) {
		dev_err(haptic->dev, "failed to set duty cycle: %d\n", error);
		return;
	}

	if (haptic->magnitude)
		max77693_haptic_enable(haptic);
	else
		max77693_haptic_disable(haptic);
}
