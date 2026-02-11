tlv320aic23_set_dai_fmt(struct snd_soc_dai *codec_dai,
				   unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 iface_reg;

	iface_reg = snd_soc_read(codec, TLV320AIC23_DIGT_FMT) & (~0x03);


	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iface_reg |= TLV320AIC23_MS_MASTER;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		iface_reg &= ~TLV320AIC23_MS_MASTER;
		break;
	default:
		return -EINVAL;

	}


	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface_reg |= TLV320AIC23_FOR_I2S;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		iface_reg |= TLV320AIC23_LRP_ON;
	case SND_SOC_DAIFMT_DSP_B:
		iface_reg |= TLV320AIC23_FOR_DSP;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		iface_reg |= TLV320AIC23_FOR_LJUST;
		break;
	default:
		return -EINVAL;

	}

	snd_soc_write(codec, TLV320AIC23_DIGT_FMT, iface_reg);

	return 0;
}
