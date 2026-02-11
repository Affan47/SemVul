twl6040_prepare(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct twl6040 *twl6040 = codec->control_data;
	struct twl6040_data *priv = snd_soc_codec_get_drvdata(codec);
	int ret;

	if (!priv->sysclk) {
		dev_err(codec->dev,
			"no mclk configured, call set_sysclk() on init\n");
		return -EINVAL;
	}

	ret = twl6040_set_pll(twl6040, priv->pll, priv->clk_in, priv->sysclk);
	if (ret) {
		dev_err(codec->dev, "Can not set PLL (%d)\n", ret);
		return -EPERM;
	}

	return 0;
}
