aic31xx_dac_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_codec *codec = codec_dai->codec;

	if (mute) {
		snd_soc_update_bits(codec, AIC31XX_DACMUTE,
				    AIC31XX_DACMUTE_MASK,
				    AIC31XX_DACMUTE_MASK);
	} else {
		snd_soc_update_bits(codec, AIC31XX_DACMUTE,
				    AIC31XX_DACMUTE_MASK, 0x0);
	}

	return 0;
}
