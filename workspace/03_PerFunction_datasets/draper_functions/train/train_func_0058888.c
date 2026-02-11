rt5640_suspend(struct snd_soc_codec *codec)
{
	struct rt5640_priv *rt5640 = snd_soc_codec_get_drvdata(codec);

	snd_soc_codec_force_bias_level(codec, SND_SOC_BIAS_OFF);
	rt5640_reset(codec);
	regcache_cache_only(rt5640->regmap, true);
	regcache_mark_dirty(rt5640->regmap);
	if (gpio_is_valid(rt5640->pdata.ldo1_en))
		gpio_set_value_cansleep(rt5640->pdata.ldo1_en, 0);

	return 0;
}
