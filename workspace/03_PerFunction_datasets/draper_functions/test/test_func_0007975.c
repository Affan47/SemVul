wm8960_put_deemph(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_soc_kcontrol_codec(kcontrol);
	struct wm8960_priv *wm8960 = snd_soc_codec_get_drvdata(codec);
	unsigned int deemph = ucontrol->value.integer.value[0];

	if (deemph > 1)
		return -EINVAL;

	wm8960->deemph = deemph;

	return wm8960_set_deemph(codec);
}
