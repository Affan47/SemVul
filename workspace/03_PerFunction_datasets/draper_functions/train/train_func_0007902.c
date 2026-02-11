mag3110_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct mag3110_data *data;
	struct iio_dev *indio_dev;
	int ret;

	ret = i2c_smbus_read_byte_data(client, MAG3110_WHO_AM_I);
	if (ret < 0)
		return ret;
	if (ret != MAG3110_DEVICE_ID)
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &mag3110_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = mag3110_channels;
	indio_dev->num_channels = ARRAY_SIZE(mag3110_channels);
	indio_dev->available_scan_masks = mag3110_scan_masks;

	data->ctrl_reg1 = MAG3110_CTRL_DR_DEFAULT << MAG3110_CTRL_DR_SHIFT;
	ret = i2c_smbus_write_byte_data(client, MAG3110_CTRL_REG1,
		data->ctrl_reg1);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(client, MAG3110_CTRL_REG2,
		MAG3110_CTRL_AUTO_MRST_EN);
	if (ret < 0)
		goto standby_on_error;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
		mag3110_trigger_handler, NULL);
	if (ret < 0)
		goto standby_on_error;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto buffer_cleanup;
	return 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
standby_on_error:
	mag3110_standby(iio_priv(indio_dev));
	return ret;
}
