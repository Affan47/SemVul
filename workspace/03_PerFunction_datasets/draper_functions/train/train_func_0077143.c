ml26124_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct ml26124_priv *priv = snd_soc_codec_get_drvdata(codec);

	switch (clk_id) {
	case ML26124_USE_PLLOUT:
		priv->clk_in = ML26124_USE_PLLOUT;
		break;
	case ML26124_USE_MCLKI:
		priv->clk_in = ML26124_USE_MCLKI;
		break;
	default:
		return -EINVAL;
	}

	priv->mclk = freq;

	return 0;
}
