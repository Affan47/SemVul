stac9766_codec_probe(struct snd_soc_codec *codec)
{
	struct snd_ac97 *ac97;

	ac97 = snd_soc_new_ac97_codec(codec, STAC9766_VENDOR_ID,
			STAC9766_VENDOR_ID_MASK);
	if (IS_ERR(ac97))
		return PTR_ERR(ac97);

	snd_soc_codec_set_drvdata(codec, ac97);

	return 0;
}
