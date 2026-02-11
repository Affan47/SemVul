dac33_hard_power(struct snd_soc_codec *codec, int power)
{
	struct tlv320dac33_priv *dac33 = snd_soc_codec_get_drvdata(codec);
	int ret = 0;

	mutex_lock(&dac33->mutex);


	if (unlikely(power == dac33->chip_power)) {
		dev_dbg(codec->dev, "Trying to set the same power state: %s\n",
			power ? "ON" : "OFF");
		goto exit;
	}

	if (power) {
		ret = regulator_bulk_enable(ARRAY_SIZE(dac33->supplies),
					  dac33->supplies);
		if (ret != 0) {
			dev_err(codec->dev,
				"Failed to enable supplies: %d\n", ret);
				goto exit;
		}

		if (dac33->power_gpio >= 0)
			gpio_set_value(dac33->power_gpio, 1);

		dac33->chip_power = 1;
	} else {
		dac33_soft_power(codec, 0);
		if (dac33->power_gpio >= 0)
			gpio_set_value(dac33->power_gpio, 0);

		ret = regulator_bulk_disable(ARRAY_SIZE(dac33->supplies),
					     dac33->supplies);
		if (ret != 0) {
			dev_err(codec->dev,
				"Failed to disable supplies: %d\n", ret);
			goto exit;
		}

		dac33->chip_power = 0;
	}

exit:
	mutex_unlock(&dac33->mutex);
	return ret;
}
