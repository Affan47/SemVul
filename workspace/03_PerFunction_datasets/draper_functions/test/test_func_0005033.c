set_dmic_clk(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);
	struct rt5645_priv *rt5645 = snd_soc_codec_get_drvdata(codec);
	int idx, rate;

	rate = rt5645->sysclk / rl6231_get_pre_div(rt5645->regmap,
		RT5645_ADDA_CLK1, RT5645_I2S_PD1_SFT);
	idx = rl6231_calc_dmic_clk(rate);
	if (idx < 0)
		dev_err(codec->dev, "Failed to set DMIC clock\n");
	else
		snd_soc_update_bits(codec, RT5645_DMIC_CTRL1,
			RT5645_DMIC_CLK_MASK, idx << RT5645_DMIC_CLK_SFT);
	return idx;
}
