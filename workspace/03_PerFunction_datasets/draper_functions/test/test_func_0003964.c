snd_microii_spdif_switch_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	u8 reg;
	int err;

	reg = ucontrol->value.integer.value[0] ? 0x28 : 0x2a;
	if (reg != list->kctl->private_value)
		return 0;

	kcontrol->private_value = reg;
	err = snd_microii_spdif_switch_update(list);
	return err < 0 ? err : 1;
}
