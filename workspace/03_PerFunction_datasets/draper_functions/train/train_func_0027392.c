max8997_haptic_disable(struct max8997_haptic *chip)
{
	mutex_lock(&chip->mutex);

	if (chip->enabled) {
		chip->enabled = false;
		max8997_haptic_configure(chip);
		if (chip->mode == MAX8997_EXTERNAL_MODE)
			pwm_disable(chip->pwm);
		regulator_disable(chip->regulator);
	}

	mutex_unlock(&chip->mutex);
}
