ms5637_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ms_tp_dev *dev_data;
	struct iio_dev *indio_dev;
	int ret;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA |
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) {
		dev_err(&client->dev,
			"Adapter does not support some i2c transaction\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*dev_data));
	if (!indio_dev)
		return -ENOMEM;

	dev_data = iio_priv(indio_dev);
	dev_data->client = client;
	dev_data->res_index = 5;
	mutex_init(&dev_data->lock);

	indio_dev->info = &ms5637_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ms5637_channels;
	indio_dev->num_channels = ARRAY_SIZE(ms5637_channels);

	i2c_set_clientdata(client, indio_dev);

	ret = ms_sensors_reset(client, 0x1E, 3000);
	if (ret)
		return ret;

	ret = ms_sensors_tp_read_prom(dev_data);
	if (ret)
		return ret;

	return devm_iio_device_register(&client->dev, indio_dev);
}
