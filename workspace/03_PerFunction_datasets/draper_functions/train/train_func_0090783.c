wm9713_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 gpio = ac97_read(codec, AC97_GPIO_CFG) & 0xffc5;
	u16 reg = 0x8000;


	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		reg |= 0x4000;
		gpio |= 0x0010;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		reg |= 0x6000;
		gpio |= 0x0018;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		reg |= 0x2000;
		gpio |= 0x001a;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		gpio |= 0x0012;
		break;
	}


	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		reg |= 0x00c0;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg |= 0x0080;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		reg |= 0x0040;
		break;
	}


	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		reg |= 0x0002;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg |= 0x0001;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		reg |= 0x0003;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		reg |= 0x0043;
		break;
	}

	ac97_write(codec, AC97_GPIO_CFG, gpio);
	ac97_write(codec, AC97_CENTER_LFE_MASTER, reg);
	return 0;
}
