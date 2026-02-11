da7219_aad_of_jack_det_rate(struct snd_soc_codec *codec, const char *str)
{
	if (!strcmp(str, "32ms_64ms")) {
		return DA7219_AAD_JACK_DET_RATE_32_64MS;
	} else if (!strcmp(str, "64ms_128ms")) {
		return DA7219_AAD_JACK_DET_RATE_64_128MS;
	} else if (!strcmp(str, "128ms_256ms")) {
		return DA7219_AAD_JACK_DET_RATE_128_256MS;
	} else if (!strcmp(str, "256ms_512ms")) {
		return DA7219_AAD_JACK_DET_RATE_256_512MS;
	} else {
		dev_warn(codec->dev, "Invalid jack detect rate");
		return DA7219_AAD_JACK_DET_RATE_256_512MS;
	}
}
