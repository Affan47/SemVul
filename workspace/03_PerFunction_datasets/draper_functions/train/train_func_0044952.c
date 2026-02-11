max98925_set_clock(struct max98925_priv *max98925,
		struct snd_pcm_hw_params *params)
{
	unsigned int dai_sr = 0, clock, mdll, n, m;
	struct snd_soc_codec *codec = max98925->codec;
	int rate = params_rate(params);

	int blr_clk_ratio = params_channels(params) * max98925->ch_size;

	switch (blr_clk_ratio) {
	case 32:
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_BSEL_MASK, M98925_DAI_BSEL_32);
		break;
	case 48:
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_BSEL_MASK, M98925_DAI_BSEL_48);
		break;
	case 64:
		regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_BSEL_MASK, M98925_DAI_BSEL_64);
		break;
	default:
		return -EINVAL;
	}

	switch (max98925->sysclk) {
	case 6000000:
		clock = 0;
		mdll  = M98925_MDLL_MULT_MCLKx16;
		break;
	case 11289600:
		clock = 1;
		mdll  = M98925_MDLL_MULT_MCLKx8;
		break;
	case 12000000:
		clock = 0;
		mdll  = M98925_MDLL_MULT_MCLKx8;
		break;
	case 12288000:
		clock = 2;
		mdll  = M98925_MDLL_MULT_MCLKx8;
		break;
	default:
		dev_info(max98925->codec->dev, "unsupported sysclk %d\n",
					max98925->sysclk);
		return -EINVAL;
	}

	if (max98925_rate_value(codec, rate, clock, &dai_sr, &n, &m))
		return -EINVAL;


	regmap_update_bits(max98925->regmap,
			MAX98925_DAI_CLK_MODE2,
			M98925_DAI_SR_MASK, dai_sr << M98925_DAI_SR_SHIFT);

	regmap_write(max98925->regmap,
		MAX98925_DAI_CLK_DIV_M_MSBS, m >> 8);
	regmap_write(max98925->regmap,
		MAX98925_DAI_CLK_DIV_M_LSBS, m & 0xFF);

	regmap_write(max98925->regmap,
		MAX98925_DAI_CLK_DIV_N_MSBS, n >> 8);
	regmap_write(max98925->regmap,
		MAX98925_DAI_CLK_DIV_N_LSBS, n & 0xFF);

	regmap_update_bits(max98925->regmap, MAX98925_DAI_CLK_MODE1,
			M98925_MDLL_MULT_MASK, mdll << M98925_MDLL_MULT_SHIFT);
	return 0;
}
