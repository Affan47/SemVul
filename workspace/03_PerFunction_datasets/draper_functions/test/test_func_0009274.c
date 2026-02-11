adau1701_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_codec *codec = dai->codec;
	unsigned int mask = ADAU1701_DSPCTRL_DAM;
	struct adau1701 *adau1701 = snd_soc_codec_get_drvdata(codec);
	unsigned int val;

	if (mute)
		val = 0;
	else
		val = mask;

	regmap_update_bits(adau1701->regmap, ADAU1701_DSPCTRL, mask, val);

	return 0;
}
