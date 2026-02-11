mixart_analog_vol_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	if(kcontrol->private_value == 0) {
		uinfo->value.integer.min = MIXART_ANALOG_PLAYBACK_LEVEL_MIN;
		uinfo->value.integer.max = MIXART_ANALOG_PLAYBACK_LEVEL_MAX;
	} else {
		uinfo->value.integer.min = MIXART_ANALOG_CAPTURE_LEVEL_MIN;
		uinfo->value.integer.max = MIXART_ANALOG_CAPTURE_LEVEL_MAX;
	}
	return 0;
}
