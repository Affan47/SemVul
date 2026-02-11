snd_fm801_put_double(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct fm801 *chip = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift_left = (kcontrol->private_value >> 8) & 0x0f;
	int shift_right = (kcontrol->private_value >> 12) & 0x0f;
	int mask = (kcontrol->private_value >> 16) & 0xff;
	int invert = (kcontrol->private_value >> 24) & 0xff;
	unsigned short val1, val2;

	val1 = ucontrol->value.integer.value[0] & mask;
	val2 = ucontrol->value.integer.value[1] & mask;
	if (invert) {
		val1 = mask - val1;
		val2 = mask - val2;
	}
	return snd_fm801_update_bits(chip, reg,
				     (mask << shift_left) | (mask << shift_right),
				     (val1 << shift_left ) | (val2 << shift_right));
}
