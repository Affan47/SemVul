tas2552_post_event(struct snd_soc_dapm_widget *w,
			      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_write(codec, TAS2552_RESERVED_0D, 0xc0);
		snd_soc_update_bits(codec, TAS2552_LIMIT_RATE_HYS, (1 << 5),
				    (1 << 5));
		snd_soc_update_bits(codec, TAS2552_CFG_2, 1, 0);
		snd_soc_update_bits(codec, TAS2552_CFG_1, TAS2552_SWS, 0);
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_update_bits(codec, TAS2552_CFG_1, TAS2552_SWS,
				    TAS2552_SWS);
		snd_soc_update_bits(codec, TAS2552_CFG_2, 1, 1);
		snd_soc_update_bits(codec, TAS2552_LIMIT_RATE_HYS, (1 << 5), 0);
		snd_soc_write(codec, TAS2552_RESERVED_0D, 0xbe);
		break;
	}
	return 0;
}
