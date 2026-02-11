ac97_volume_put(struct snd_kcontrol *ctl,
			   struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	unsigned int codec = (ctl->private_value >> 24) & 1;
	int stereo = (ctl->private_value >> 16) & 1;
	unsigned int index = ctl->private_value & 0xff;
	u16 oldreg, newreg;
	int change;

	mutex_lock(&chip->mutex);
	oldreg = oxygen_read_ac97(chip, codec, index);
	if (!stereo) {
		newreg = oldreg & ~0x1f;
		newreg |= 31 - (value->value.integer.value[0] & 0x1f);
	} else {
		newreg = oldreg & ~0x1f1f;
		newreg |= (31 - (value->value.integer.value[0] & 0x1f)) << 8;
		newreg |= 31 - (value->value.integer.value[1] & 0x1f);
	}
	change = newreg != oldreg;
	if (change)
		oxygen_write_ac97(chip, codec, index, newreg);
	mutex_unlock(&chip->mutex);
	return change;
}
