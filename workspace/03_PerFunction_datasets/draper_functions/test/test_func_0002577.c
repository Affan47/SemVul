snd_trident_pcm_vol_control_get(struct snd_kcontrol *kcontrol,
					   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_trident *trident = snd_kcontrol_chip(kcontrol);
	struct snd_trident_pcm_mixer *mix = &trident->pcm_mixer[snd_ctl_get_ioffnum(kcontrol, &ucontrol->id)];

	if (trident->device == TRIDENT_DEVICE_ID_SI7018) {
		ucontrol->value.integer.value[0] = 1023 - mix->vol;
	} else {
		ucontrol->value.integer.value[0] = 255 - (mix->vol>>2);
	}
	return 0;
}
