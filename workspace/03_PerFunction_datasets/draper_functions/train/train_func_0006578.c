usb6fire_control_output_mute_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct control_runtime *rt = snd_kcontrol_chip(kcontrol);
	unsigned int ch = kcontrol->private_value;
	u8 value = rt->output_mute >> ch;

	if (ch > 4) {
		dev_err(&rt->chip->dev->dev,
			"Invalid channel in volume control.");
		return -EINVAL;
	}

	ucontrol->value.integer.value[0] = 1 & value;
	value >>= 1;
	ucontrol->value.integer.value[1] = 1 & value;

	return 0;
}
