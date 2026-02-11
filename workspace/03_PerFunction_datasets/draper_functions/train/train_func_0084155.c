adau17x1_set_dai_sysclk(struct snd_soc_dai *dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(dai->codec);
	struct adau *adau = snd_soc_codec_get_drvdata(dai->codec);

	switch (clk_id) {
	case ADAU17X1_CLK_SRC_MCLK:
	case ADAU17X1_CLK_SRC_PLL:
		break;
	default:
		return -EINVAL;
	}

	adau->sysclk = freq;

	if (adau->clk_src != clk_id) {
		if (clk_id == ADAU17X1_CLK_SRC_PLL) {
			snd_soc_dapm_add_routes(dapm,
				&adau17x1_dapm_pll_route, 1);
		} else {
			snd_soc_dapm_del_routes(dapm,
				&adau17x1_dapm_pll_route, 1);
		}
	}

	adau->clk_src = clk_id;

	return 0;
}
