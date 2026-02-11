snd_at73c213_mono_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 8) & 0xff;
	int mask = (kcontrol->private_value >> 16) & 0xff;
	int invert = (kcontrol->private_value >> 24) & 0xff;

	mutex_lock(&chip->mixer_lock);

	ucontrol->value.integer.value[0] =
		(chip->reg_image[reg] >> shift) & mask;

	if (invert)
		ucontrol->value.integer.value[0] =
			mask - ucontrol->value.integer.value[0];

	mutex_unlock(&chip->mixer_lock);

	return 0;
}
