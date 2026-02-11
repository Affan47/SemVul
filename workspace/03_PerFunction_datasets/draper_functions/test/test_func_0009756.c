ms5611_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct ms5611_state *st;
	struct iio_dev *indio_dev;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_WORD_DATA |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	st->reset = ms5611_i2c_reset;
	st->read_prom_word = ms5611_i2c_read_prom_word;
	st->read_adc_temp_and_pressure = ms5611_i2c_read_adc_temp_and_pressure;
	st->client = client;

	return ms5611_probe(indio_dev, &client->dev, id->driver_data);
}
