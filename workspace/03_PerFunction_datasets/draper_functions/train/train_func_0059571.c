ak4642_dai_set_sysclk(struct snd_soc_dai *codec_dai,
	int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct ak4642_priv *priv = snd_soc_codec_get_drvdata(codec);
	u8 pll;
	int extended_freq = 0;

	switch (freq) {
	case 11289600:
		pll = PLL2;
		break;
	case 12288000:
		pll = PLL2 | PLL0;
		break;
	case 12000000:
		pll = PLL2 | PLL1;
		break;
	case 24000000:
		pll = PLL2 | PLL1 | PLL0;
		break;
	case 13500000:
		pll = PLL3 | PLL2;
		break;
	case 27000000:
		pll = PLL3 | PLL2 | PLL0;
		break;
	case 19200000:
		pll = PLL3;
		extended_freq = 1;
		break;
	case 13000000:
		pll = PLL3 | PLL2 | PLL1;
		extended_freq = 1;
		break;
	case 26000000:
		pll = PLL3 | PLL2 | PLL1 | PLL0;
		extended_freq = 1;
		break;
	default:
		return -EINVAL;
	}

	if (extended_freq && !priv->drvdata->extended_frequencies)
		return -EINVAL;

	snd_soc_update_bits(codec, MD_CTL1, PLL_MASK, pll);

	return 0;
}
