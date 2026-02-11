snd_at73c213_stereo_info(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo)
{
	int mask = (kcontrol->private_value >> 24) & 0xff;

	if (mask == 1)
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	else
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;

	uinfo->count = 2;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = mask;

	return 0;
}
