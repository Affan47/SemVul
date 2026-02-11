aic31xx_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				  int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	int i;

	dev_dbg(codec->dev, "## %s: clk_id = %d, freq = %d, dir = %d\n",
		__func__, clk_id, freq, dir);

	for (i = 1; freq/i > 20000000 && i < 8; i++)
		;
	if (freq/i > 20000000) {
		dev_err(aic31xx->dev, "%s: Too high mclk frequency %u\n",
			__func__, freq);
			return -EINVAL;
	}
	aic31xx->p_div = i;

	for (i = 0; i < ARRAY_SIZE(aic31xx_divs) &&
		     aic31xx_divs[i].mclk_p != freq/aic31xx->p_div; i++)
		;
	if (i == ARRAY_SIZE(aic31xx_divs)) {
		dev_err(aic31xx->dev, "%s: Unsupported frequency %d\n",
			__func__, freq);
		return -EINVAL;
	}


	snd_soc_update_bits(codec, AIC31XX_CLKMUX, AIC31XX_PLL_CLKIN_MASK,
			    clk_id << AIC31XX_PLL_CLKIN_SHIFT);

	aic31xx->sysclk = freq;
	return 0;
}
