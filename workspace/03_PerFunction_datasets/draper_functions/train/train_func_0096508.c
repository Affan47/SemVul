snd_ymfpci_info_double(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	unsigned int reg = kcontrol->private_value;

	if (reg < 0x80 || reg >= 0xc0)
		return -EINVAL;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = 16383;
	return 0;
}
