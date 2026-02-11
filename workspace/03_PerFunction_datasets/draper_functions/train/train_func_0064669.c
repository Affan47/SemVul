wm8750_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8750_priv *wm8750;
	struct regmap *regmap;
	int ret;

	wm8750 = devm_kzalloc(&i2c->dev, sizeof(struct wm8750_priv),
			      GFP_KERNEL);
	if (wm8750 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, wm8750);

	regmap = devm_regmap_init_i2c(i2c, &wm8750_regmap);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret =  snd_soc_register_codec(&i2c->dev,
			&soc_codec_dev_wm8750, &wm8750_dai, 1);
	return ret;
}
