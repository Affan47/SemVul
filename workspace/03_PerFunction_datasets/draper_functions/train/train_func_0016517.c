max98090_dai_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *params,
				   struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct max98090_priv *max98090 = snd_soc_codec_get_drvdata(codec);
	struct max98090_cdata *cdata;

	cdata = &max98090->dai[0];
	max98090->bclk = snd_soc_params_to_bclk(params);
	if (params_channels(params) == 1)
		max98090->bclk *= 2;

	max98090->lrclk = params_rate(params);

	switch (params_width(params)) {
	case 16:
		snd_soc_update_bits(codec, M98090_REG_INTERFACE_FORMAT,
			M98090_WS_MASK, 0);
		break;
	default:
		return -EINVAL;
	}

	if (max98090->master)
		max98090_configure_bclk(codec);

	cdata->rate = max98090->lrclk;


	if (max98090->lrclk < 24000)
		snd_soc_update_bits(codec, M98090_REG_FILTER_CONFIG,
			M98090_MODE_MASK, 0);
	else
		snd_soc_update_bits(codec, M98090_REG_FILTER_CONFIG,
			M98090_MODE_MASK, M98090_MODE_MASK);


	if (max98090->lrclk < 50000)
		snd_soc_update_bits(codec, M98090_REG_FILTER_CONFIG,
			M98090_DHF_MASK, 0);
	else
		snd_soc_update_bits(codec, M98090_REG_FILTER_CONFIG,
			M98090_DHF_MASK, M98090_DHF_MASK);

	max98090_configure_dmic(max98090, max98090->dmic_freq, max98090->pclk,
				max98090->lrclk);

	return 0;
}
