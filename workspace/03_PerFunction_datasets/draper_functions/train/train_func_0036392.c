lola_analog_vol_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct lola *chip = snd_kcontrol_chip(kcontrol);
	int dir = kcontrol->private_value;
	int i;

	for (i = 0; i < chip->pin[dir].num_pins; i++)
		ucontrol->value.integer.value[i] =
			chip->pin[dir].pins[i].cur_gain_step;
	return 0;
}
