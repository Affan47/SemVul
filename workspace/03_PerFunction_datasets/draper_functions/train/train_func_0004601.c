atmel_classd_codec_dai_digital_mute(struct snd_soc_dai *codec_dai,
	int mute)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u32 mask, val;

	mask = CLASSD_MR_LMUTE_MASK | CLASSD_MR_RMUTE_MASK;

	if (mute)
		val = mask;
	else
		val = 0;

	snd_soc_update_bits(codec, CLASSD_MR, mask, val);

	return 0;
}
