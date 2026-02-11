cs4349_set_dai_fmt(struct snd_soc_dai *codec_dai,
			      unsigned int format)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct cs4349_private *cs4349 = snd_soc_codec_get_drvdata(codec);
	unsigned int fmt;

	fmt = format & SND_SOC_DAIFMT_FORMAT_MASK;

	switch (fmt) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_LEFT_J:
	case SND_SOC_DAIFMT_RIGHT_J:
		cs4349->mode = format & SND_SOC_DAIFMT_FORMAT_MASK;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
