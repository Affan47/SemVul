rt298_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_codec *codec = dai->codec;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_update_bits(codec,
			RT298_I2S_CTRL1, 0x800, 0x800);
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_update_bits(codec,
			RT298_I2S_CTRL1, 0x800, 0x0);
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		snd_soc_update_bits(codec,
			RT298_I2S_CTRL1, 0x300, 0x0);
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		snd_soc_update_bits(codec,
			RT298_I2S_CTRL1, 0x300, 0x1 << 8);
		break;
	case SND_SOC_DAIFMT_DSP_A:
		snd_soc_update_bits(codec,
			RT298_I2S_CTRL1, 0x300, 0x2 << 8);
		break;
	case SND_SOC_DAIFMT_DSP_B:
		snd_soc_update_bits(codec,
			RT298_I2S_CTRL1, 0x300, 0x3 << 8);
		break;
	default:
		return -EINVAL;
	}

	snd_soc_update_bits(codec, RT298_DAC_FORMAT, 0x8000, 0);
	snd_soc_update_bits(codec, RT298_ADC_FORMAT, 0x8000, 0);

	return 0;
}
