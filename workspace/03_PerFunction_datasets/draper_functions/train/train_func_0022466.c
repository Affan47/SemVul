da7219_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
			      int source, unsigned int fref, unsigned int fout)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct da7219_priv *da7219 = snd_soc_codec_get_drvdata(codec);

	u8 pll_ctrl, indiv_bits, indiv;
	u8 pll_frac_top, pll_frac_bot, pll_integer;
	u32 freq_ref;
	u64 frac_div;


	if (da7219->mclk_rate == 32768) {
		indiv_bits = DA7219_PLL_INDIV_2_5_MHZ;
		indiv = DA7219_PLL_INDIV_2_5_MHZ_VAL;
	} else if (da7219->mclk_rate < 2000000) {
		dev_err(codec->dev, "PLL input clock %d below valid range\n",
			da7219->mclk_rate);
		return -EINVAL;
	} else if (da7219->mclk_rate <= 5000000) {
		indiv_bits = DA7219_PLL_INDIV_2_5_MHZ;
		indiv = DA7219_PLL_INDIV_2_5_MHZ_VAL;
	} else if (da7219->mclk_rate <= 10000000) {
		indiv_bits = DA7219_PLL_INDIV_5_10_MHZ;
		indiv = DA7219_PLL_INDIV_5_10_MHZ_VAL;
	} else if (da7219->mclk_rate <= 20000000) {
		indiv_bits = DA7219_PLL_INDIV_10_20_MHZ;
		indiv = DA7219_PLL_INDIV_10_20_MHZ_VAL;
	} else if (da7219->mclk_rate <= 40000000) {
		indiv_bits = DA7219_PLL_INDIV_20_40_MHZ;
		indiv = DA7219_PLL_INDIV_20_40_MHZ_VAL;
	} else if (da7219->mclk_rate <= 54000000) {
		indiv_bits = DA7219_PLL_INDIV_40_54_MHZ;
		indiv = DA7219_PLL_INDIV_40_54_MHZ_VAL;
	} else {
		dev_err(codec->dev, "PLL input clock %d above valid range\n",
			da7219->mclk_rate);
		return -EINVAL;
	}
	freq_ref = (da7219->mclk_rate / indiv);
	pll_ctrl = indiv_bits;


	switch (source) {
	case DA7219_SYSCLK_MCLK:
		pll_ctrl |= DA7219_PLL_MODE_BYPASS;
		snd_soc_update_bits(codec, DA7219_PLL_CTRL,
				    DA7219_PLL_INDIV_MASK |
				    DA7219_PLL_MODE_MASK, pll_ctrl);
		return 0;
	case DA7219_SYSCLK_PLL:
		pll_ctrl |= DA7219_PLL_MODE_NORMAL;
		break;
	case DA7219_SYSCLK_PLL_SRM:
		pll_ctrl |= DA7219_PLL_MODE_SRM;
		break;
	case DA7219_SYSCLK_PLL_32KHZ:
		pll_ctrl |= DA7219_PLL_MODE_32KHZ;
		break;
	default:
		dev_err(codec->dev, "Invalid PLL config\n");
		return -EINVAL;
	}


	pll_integer = fout / freq_ref;
	frac_div = (u64)(fout % freq_ref) * 8192ULL;
	do_div(frac_div, freq_ref);
	pll_frac_top = (frac_div >> DA7219_BYTE_SHIFT) & DA7219_BYTE_MASK;
	pll_frac_bot = (frac_div) & DA7219_BYTE_MASK;


	snd_soc_write(codec, DA7219_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_write(codec, DA7219_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_write(codec, DA7219_PLL_INTEGER, pll_integer);
	snd_soc_update_bits(codec, DA7219_PLL_CTRL,
			    DA7219_PLL_INDIV_MASK | DA7219_PLL_MODE_MASK,
			    pll_ctrl);

	return 0;
}
