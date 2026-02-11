control_get(struct snd_kcontrol *kcontrol,
		       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_usb_audio *chip = snd_kcontrol_chip(kcontrol);
	struct snd_usb_caiaqdev *cdev = caiaqdev(chip->card);
	int pos = kcontrol->private_value;

	if (pos & CNT_INTVAL)
		ucontrol->value.integer.value[0]
			= cdev->control_state[pos & ~CNT_INTVAL];
	else
		ucontrol->value.integer.value[0]
			= !!(cdev->control_state[pos / 8] & (1 << pos % 8));

	return 0;
}
