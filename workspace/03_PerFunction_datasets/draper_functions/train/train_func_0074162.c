fsl_asoc_card_late_probe(struct snd_soc_card *card)
{
	struct fsl_asoc_card_priv *priv = snd_soc_card_get_drvdata(card);
	struct snd_soc_dai *codec_dai = card->rtd[0].codec_dai;
	struct codec_priv *codec_priv = &priv->codec_priv;
	struct device *dev = card->dev;
	int ret;

	if (fsl_asoc_card_is_ac97(priv)) {
#if IS_ENABLED(CONFIG_SND_AC97_CODEC)
		struct snd_soc_codec *codec = card->rtd[0].codec;
		struct snd_ac97 *ac97 = snd_soc_codec_get_drvdata(codec);


		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_SPSA_SLOT_MASK, AC97_EA_SPSA_3_4);
#endif

		return 0;
	}

	ret = snd_soc_dai_set_sysclk(codec_dai, codec_priv->mclk_id,
				     codec_priv->mclk_freq, SND_SOC_CLOCK_IN);
	if (ret) {
		dev_err(dev, "failed to set sysclk in %s\n", __func__);
		return ret;
	}

	return 0;
}
