ac97_fp_rec_volume_put(struct snd_kcontrol *ctl,
				  struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	u16 oldreg, newreg;
	int change;

	mutex_lock(&chip->mutex);
	oldreg = oxygen_read_ac97(chip, 1, AC97_REC_GAIN);
	newreg = oldreg & ~0x0707;
	newreg = newreg | (value->value.integer.value[0] & 7);
	newreg = newreg | ((value->value.integer.value[0] & 7) << 8);
	change = newreg != oldreg;
	if (change)
		oxygen_write_ac97(chip, 1, AC97_REC_GAIN, newreg);
	mutex_unlock(&chip->mutex);
	return change;
}
