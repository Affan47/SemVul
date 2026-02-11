max98095_lineout_event(struct snd_soc_dapm_widget *w,
			     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_update_bits(codec, w->reg,
			(1 << (w->shift+2)), (1 << (w->shift+2)));
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_update_bits(codec, w->reg,
			(1 << (w->shift+2)), 0);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
