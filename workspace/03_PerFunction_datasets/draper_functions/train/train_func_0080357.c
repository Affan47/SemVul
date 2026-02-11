rt5660_set_bias_level(struct snd_soc_codec *codec,
			enum snd_soc_bias_level level)
{
	struct rt5660_priv *rt5660 = snd_soc_codec_get_drvdata(codec);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		snd_soc_update_bits(codec, RT5660_GEN_CTRL1,
			RT5660_DIG_GATE_CTRL, RT5660_DIG_GATE_CTRL);

		if (IS_ERR(rt5660->mclk))
			break;

		if (snd_soc_codec_get_bias_level(codec) == SND_SOC_BIAS_ON) {
			clk_disable_unprepare(rt5660->mclk);
		} else {
			ret = clk_prepare_enable(rt5660->mclk);
			if (ret)
				return ret;
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_codec_get_bias_level(codec) == SND_SOC_BIAS_OFF) {
			snd_soc_update_bits(codec, RT5660_PWR_ANLG1,
				RT5660_PWR_VREF1 | RT5660_PWR_MB |
				RT5660_PWR_BG | RT5660_PWR_VREF2,
				RT5660_PWR_VREF1 | RT5660_PWR_MB |
				RT5660_PWR_BG | RT5660_PWR_VREF2);
			usleep_range(10000, 15000);
			snd_soc_update_bits(codec, RT5660_PWR_ANLG1,
				RT5660_PWR_FV1 | RT5660_PWR_FV2,
				RT5660_PWR_FV1 | RT5660_PWR_FV2);
		}
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_update_bits(codec, RT5660_GEN_CTRL1,
			RT5660_DIG_GATE_CTRL, 0);
		break;

	default:
		break;
	}

	return 0;
}
