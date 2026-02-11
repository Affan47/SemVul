jsa1212_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct jsa1212_data *data;
	struct iio_dev *indio_dev;
	struct regmap *regmap;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &jsa1212_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Regmap initialization failed.\n");
		return PTR_ERR(regmap);
	}

	data = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	mutex_init(&data->lock);

	ret = jsa1212_chip_init(data);
	if (ret < 0)
		return ret;

	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = jsa1212_channels;
	indio_dev->num_channels = ARRAY_SIZE(jsa1212_channels);
	indio_dev->name = JSA1212_DRIVER_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	indio_dev->info = &jsa1212_info;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		dev_err(&client->dev, "%s: register device failed\n", __func__);

	return ret;
}
