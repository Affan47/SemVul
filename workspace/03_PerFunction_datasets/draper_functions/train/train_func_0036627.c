cx20442_set_bias_level(struct snd_soc_codec *codec,
		enum snd_soc_bias_level level)
{
	struct cx20442_priv *cx20442 = snd_soc_codec_get_drvdata(codec);
	int err = 0;

	switch (level) {
	case SND_SOC_BIAS_PREPARE:
		if (snd_soc_codec_get_bias_level(codec) != SND_SOC_BIAS_STANDBY)
			break;
		if (IS_ERR(cx20442->por))
			err = PTR_ERR(cx20442->por);
		else
			err = regulator_enable(cx20442->por);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_codec_get_bias_level(codec) != SND_SOC_BIAS_PREPARE)
			break;
		if (IS_ERR(cx20442->por))
			err = PTR_ERR(cx20442->por);
		else
			err = regulator_disable(cx20442->por);
		break;
	default:
		break;
	}

	return err;
}
