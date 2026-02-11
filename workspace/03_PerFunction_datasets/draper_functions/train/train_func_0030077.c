max98095_suspend(struct snd_soc_codec *codec)
{
	struct max98095_priv *max98095 = snd_soc_codec_get_drvdata(codec);

	if (max98095->headphone_jack || max98095->mic_jack)
		max98095_jack_detect_disable(codec);

	snd_soc_codec_force_bias_level(codec, SND_SOC_BIAS_OFF);

	return 0;
}
