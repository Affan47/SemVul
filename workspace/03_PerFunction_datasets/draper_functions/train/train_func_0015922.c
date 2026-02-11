cs4271_codec_remove(struct snd_soc_codec *codec)
{
	struct cs4271_private *cs4271 = snd_soc_codec_get_drvdata(codec);

	if (gpio_is_valid(cs4271->gpio_nreset))

		gpio_set_value(cs4271->gpio_nreset, 0);

	return 0;
}
