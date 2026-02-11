ct_alsa_mix_volume_get(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	struct ct_atc *atc = snd_kcontrol_chip(kcontrol);
	enum CT_AMIXER_CTL type = get_amixer_index(kcontrol->private_value);
	struct amixer *amixer;
	int i, val;

	for (i = 0; i < 2; i++) {
		amixer = ((struct ct_mixer *)atc->mixer)->
						amixers[type*CHN_NUM+i];
		val = amixer->ops->get_scale(amixer) / VOL_SCALE;
		if (val < 0)
			val = 0;
		else if (val > VOL_MAX)
			val = VOL_MAX;
		ucontrol->value.integer.value[i] = val;
	}

	return 0;
}
