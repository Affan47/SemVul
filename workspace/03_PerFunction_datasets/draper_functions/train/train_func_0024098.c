wm8993_set_dai_fmt(struct snd_soc_dai *dai,
			      unsigned int fmt)
{
	struct snd_soc_codec *codec = dai->codec;
	struct wm8993_priv *wm8993 = snd_soc_codec_get_drvdata(codec);
	unsigned int aif1 = snd_soc_read(codec, WM8993_AUDIO_INTERFACE_1);
	unsigned int aif4 = snd_soc_read(codec, WM8993_AUDIO_INTERFACE_4);

	aif1 &= ~(WM8993_BCLK_DIR | WM8993_AIF_BCLK_INV |
		  WM8993_AIF_LRCLK_INV | WM8993_AIF_FMT_MASK);
	aif4 &= ~WM8993_LRCLK_DIR;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		wm8993->master = 0;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		aif4 |= WM8993_LRCLK_DIR;
		wm8993->master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		aif1 |= WM8993_BCLK_DIR;
		wm8993->master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		aif1 |= WM8993_BCLK_DIR;
		aif4 |= WM8993_LRCLK_DIR;
		wm8993->master = 1;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_B:
		aif1 |= WM8993_AIF_LRCLK_INV;
	case SND_SOC_DAIFMT_DSP_A:
		aif1 |= 0x18;
		break;
	case SND_SOC_DAIFMT_I2S:
		aif1 |= 0x10;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif1 |= 0x8;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:

		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8993_AIF_BCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;

	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_RIGHT_J:
	case SND_SOC_DAIFMT_LEFT_J:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_IF:
			aif1 |= WM8993_AIF_BCLK_INV | WM8993_AIF_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8993_AIF_BCLK_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			aif1 |= WM8993_AIF_LRCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	snd_soc_write(codec, WM8993_AUDIO_INTERFACE_1, aif1);
	snd_soc_write(codec, WM8993_AUDIO_INTERFACE_4, aif4);

	return 0;
}
