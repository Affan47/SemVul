wm831x_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm831x *wm831x;
	int ret;

	wm831x = devm_kzalloc(&i2c->dev, sizeof(struct wm831x), GFP_KERNEL);
	if (wm831x == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, wm831x);
	wm831x->dev = &i2c->dev;

	wm831x->regmap = devm_regmap_init_i2c(i2c, &wm831x_regmap_config);
	if (IS_ERR(wm831x->regmap)) {
		ret = PTR_ERR(wm831x->regmap);
		dev_err(wm831x->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	return wm831x_device_init(wm831x, id->driver_data, i2c->irq);
}
