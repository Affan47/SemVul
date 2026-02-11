headsetlpga_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);
	struct twl4030_priv *twl4030 = snd_soc_codec_get_drvdata(codec);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:

		if (!twl4030->hsr_enabled)
			headset_ramp(codec, 1);

		twl4030->hsl_enabled = 1;
		break;
	case SND_SOC_DAPM_POST_PMD:

		if (!twl4030->hsr_enabled)
			headset_ramp(codec, 0);

		twl4030->hsl_enabled = 0;
		break;
	}
	return 0;
}
