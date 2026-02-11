max9768_probe(struct snd_soc_component *component)
{
	struct max9768 *max9768 = snd_soc_component_get_drvdata(component);
	int ret;

	if (max9768->flags & MAX9768_FLAG_CLASSIC_PWM) {
		ret = regmap_write(max9768->regmap, MAX9768_CTRL,
			MAX9768_CTRL_PWM);
		if (ret)
			return ret;
	}

	if (gpio_is_valid(max9768->mute_gpio)) {
		ret = snd_soc_add_component_controls(component, max9768_mute,
				ARRAY_SIZE(max9768_mute));
		if (ret)
			return ret;
	}

	return 0;
}
