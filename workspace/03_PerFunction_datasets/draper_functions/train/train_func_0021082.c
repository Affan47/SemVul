wm8753_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8753_priv *wm8753;
	int ret;

	wm8753 = devm_kzalloc(&i2c->dev, sizeof(struct wm8753_priv),
			      GFP_KERNEL);
	if (wm8753 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, wm8753);

	wm8753->regmap = devm_regmap_init_i2c(i2c, &wm8753_regmap);
	if (IS_ERR(wm8753->regmap)) {
		ret = PTR_ERR(wm8753->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = snd_soc_register_codec(&i2c->dev, &soc_codec_dev_wm8753,
				     wm8753_dai, ARRAY_SIZE(wm8753_dai));
	if (ret != 0)
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);

	return ret;
}
