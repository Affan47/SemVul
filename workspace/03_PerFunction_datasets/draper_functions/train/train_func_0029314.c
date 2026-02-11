sgtl5000_set_bias_level(struct snd_soc_codec *codec,
				   enum snd_soc_bias_level level)
{
	int ret;
	struct sgtl5000_priv *sgtl5000 = snd_soc_codec_get_drvdata(codec);

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_codec_get_bias_level(codec) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(
						ARRAY_SIZE(sgtl5000->supplies),
						sgtl5000->supplies);
			if (ret)
				return ret;
			udelay(10);

			regcache_cache_only(sgtl5000->regmap, false);

			ret = regcache_sync(sgtl5000->regmap);
			if (ret != 0) {
				dev_err(codec->dev,
					"Failed to restore cache: %d\n", ret);

				regcache_cache_only(sgtl5000->regmap, true);
				regulator_bulk_disable(ARRAY_SIZE(sgtl5000->supplies),
						       sgtl5000->supplies);

				return ret;
			}
		}

		break;
	case SND_SOC_BIAS_OFF:
		regcache_cache_only(sgtl5000->regmap, true);
		regulator_bulk_disable(ARRAY_SIZE(sgtl5000->supplies),
					sgtl5000->supplies);
		break;
	}

	return 0;
}
