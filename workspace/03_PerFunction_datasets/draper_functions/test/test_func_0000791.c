adau17x1_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct adau *adau = snd_soc_codec_get_drvdata(codec);
	unsigned int val, div, dsp_div;
	unsigned int freq;
	int ret;

	if (adau->clk_src == ADAU17X1_CLK_SRC_PLL)
		freq = adau->pll_freq;
	else
		freq = adau->sysclk;

	if (freq % params_rate(params) != 0)
		return -EINVAL;

	switch (freq / params_rate(params)) {
	case 1024:
		div = 0;
		dsp_div = 1;
		break;
	case 6144:
		div = 1;
		dsp_div = 6;
		break;
	case 4096:
		div = 2;
		dsp_div = 5;
		break;
	case 3072:
		div = 3;
		dsp_div = 4;
		break;
	case 2048:
		div = 4;
		dsp_div = 3;
		break;
	case 1536:
		div = 5;
		dsp_div = 2;
		break;
	case 512:
		div = 6;
		dsp_div = 0;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_CONVSR_MASK, div);
	if (adau17x1_has_dsp(adau)) {
		regmap_write(adau->regmap, ADAU17X1_SERIAL_SAMPLING_RATE, div);
		regmap_write(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, dsp_div);
	}

	if (adau->sigmadsp) {
		ret = adau17x1_setup_firmware(adau, params_rate(params));
		if (ret < 0)
			return ret;
	}

	if (adau->dai_fmt != SND_SOC_DAIFMT_RIGHT_J)
		return 0;

	switch (params_width(params)) {
	case 16:
		val = ADAU17X1_SERIAL_PORT1_DELAY16;
		break;
	case 24:
		val = ADAU17X1_SERIAL_PORT1_DELAY8;
		break;
	case 32:
		val = ADAU17X1_SERIAL_PORT1_DELAY0;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(adau->regmap, ADAU17X1_SERIAL_PORT1,
			ADAU17X1_SERIAL_PORT1_DELAY_MASK, val);
}
