snd_wl1273_fm_audio_put(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_soc_kcontrol_codec(kcontrol);
	struct wl1273_priv *wl1273 = snd_soc_codec_get_drvdata(codec);
	int val, r = 0;

	dev_dbg(codec->dev, "%s: enter.\n", __func__);

	val = ucontrol->value.integer.value[0];
	if (wl1273->core->audio_mode == val)
		return 0;

	r = wl1273->core->set_audio(wl1273->core, val);
	if (r < 0)
		return r;

	return 1;
}
