aic31xx_power_on(struct snd_soc_codec *codec)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	int ret = 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(aic31xx->supplies),
				    aic31xx->supplies);
	if (ret)
		return ret;

	if (gpio_is_valid(aic31xx->pdata.gpio_reset)) {
		gpio_set_value(aic31xx->pdata.gpio_reset, 1);
		udelay(100);
	}
	regcache_cache_only(aic31xx->regmap, false);
	ret = regcache_sync(aic31xx->regmap);
	if (ret != 0) {
		dev_err(codec->dev,
			"Failed to restore cache: %d\n", ret);
		regcache_cache_only(aic31xx->regmap, true);
		regulator_bulk_disable(ARRAY_SIZE(aic31xx->supplies),
				       aic31xx->supplies);
		return ret;
	}
	return 0;
}
