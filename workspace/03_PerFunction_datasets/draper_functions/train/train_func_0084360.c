alc5623_resume(struct snd_soc_codec *codec)
{
	struct alc5623_priv *alc5623 = snd_soc_codec_get_drvdata(codec);
	int ret;


	regcache_cache_only(alc5623->regmap, false);
	ret = regcache_sync(alc5623->regmap);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to sync register cache: %d\n",
			ret);
		regcache_cache_only(alc5623->regmap, true);
		return ret;
	}

	return 0;
}
