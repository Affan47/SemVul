ab8500_audio_setup_mics(struct snd_soc_codec *codec,
			struct amic_settings *amics)
{
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);
	u8 value8;
	unsigned int value;
	int status;
	const struct snd_soc_dapm_route *route;

	dev_dbg(codec->dev, "%s: Enter.\n", __func__);


	status = abx500_get_register_interruptible(codec->dev, AB8500_MISC,
						AB8500_GPIO_DIR4_REG,
						&value8);
	if (status < 0)
		return status;
	value = value8 | GPIO27_DIR_OUTPUT | GPIO29_DIR_OUTPUT |
		GPIO31_DIR_OUTPUT;
	status = abx500_set_register_interruptible(codec->dev,
						AB8500_MISC,
						AB8500_GPIO_DIR4_REG,
						value);
	if (status < 0)
		return status;


	dev_dbg(codec->dev, "%s: Mic 1a regulator: %s\n", __func__,
		amic_micbias_str(amics->mic1a_micbias));
	route = &ab8500_dapm_routes_mic1a_vamicx[amics->mic1a_micbias];
	status = snd_soc_dapm_add_routes(dapm, route, 1);
	dev_dbg(codec->dev, "%s: Mic 1b regulator: %s\n", __func__,
		amic_micbias_str(amics->mic1b_micbias));
	route = &ab8500_dapm_routes_mic1b_vamicx[amics->mic1b_micbias];
	status |= snd_soc_dapm_add_routes(dapm, route, 1);
	dev_dbg(codec->dev, "%s: Mic 2 regulator: %s\n", __func__,
		amic_micbias_str(amics->mic2_micbias));
	route = &ab8500_dapm_routes_mic2_vamicx[amics->mic2_micbias];
	status |= snd_soc_dapm_add_routes(dapm, route, 1);
	if (status < 0) {
		dev_err(codec->dev,
			"%s: Failed to add AMic-regulator DAPM-routes (%d).\n",
			__func__, status);
		return status;
	}


	dev_dbg(codec->dev, "%s: Mic 1 mic-type: %s\n", __func__,
		amic_type_str(amics->mic1_type));
	snd_soc_update_bits(codec, AB8500_ANAGAIN1, AB8500_ANAGAINX_ENSEMICX,
			amics->mic1_type == AMIC_TYPE_DIFFERENTIAL ?
				0 : AB8500_ANAGAINX_ENSEMICX);
	dev_dbg(codec->dev, "%s: Mic 2 mic-type: %s\n", __func__,
		amic_type_str(amics->mic2_type));
	snd_soc_update_bits(codec, AB8500_ANAGAIN2, AB8500_ANAGAINX_ENSEMICX,
			amics->mic2_type == AMIC_TYPE_DIFFERENTIAL ?
				0 : AB8500_ANAGAINX_ENSEMICX);

	return 0;
}
