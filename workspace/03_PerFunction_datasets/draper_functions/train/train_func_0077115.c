adau1977_mute(struct snd_soc_dai *dai, int mute, int stream)
{
	struct adau1977 *adau1977 = snd_soc_codec_get_drvdata(dai->codec);
	unsigned int val;

	if (mute)
		val = ADAU1977_MISC_CONTROL_MMUTE;
	else
		val = 0;

	return regmap_update_bits(adau1977->regmap, ADAU1977_REG_MISC_CONTROL,
			ADAU1977_MISC_CONTROL_MMUTE, val);
}
