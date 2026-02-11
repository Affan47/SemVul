arizona_dvfs_enable(struct snd_soc_codec *codec)
{
	const struct arizona_priv *priv = snd_soc_codec_get_drvdata(codec);
	struct arizona *arizona = priv->arizona;
	int ret;

	ret = regulator_set_voltage(arizona->dcvdd, 1800000, 1800000);
	if (ret) {
		dev_err(codec->dev, "Failed to boost DCVDD: %d\n", ret);
		return ret;
	}

	ret = regmap_update_bits(arizona->regmap,
				 ARIZONA_DYNAMIC_FREQUENCY_SCALING_1,
				 ARIZONA_SUBSYS_MAX_FREQ,
				 ARIZONA_SUBSYS_MAX_FREQ);
	if (ret) {
		dev_err(codec->dev, "Failed to enable subsys max: %d\n", ret);
		regulator_set_voltage(arizona->dcvdd, 1200000, 1800000);
		return ret;
	}

	return 0;
}
