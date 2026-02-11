stk3310_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int ret;
	struct iio_dev *indio_dev;
	struct stk3310_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev) {
		dev_err(&client->dev, "iio allocation failed!\n");
		return -ENOMEM;
	}

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);

	ret = stk3310_regmap_init(data);
	if (ret < 0)
		return ret;

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &stk3310_info;
	indio_dev->name = STK3310_DRIVER_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = stk3310_channels;
	indio_dev->num_channels = ARRAY_SIZE(stk3310_channels);

	ret = stk3310_init(indio_dev);
	if (ret < 0)
		return ret;

	if (client->irq > 0) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						stk3310_irq_handler,
						stk3310_irq_event_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						STK3310_EVENT, indio_dev);
		if (ret < 0) {
			dev_err(&client->dev, "request irq %d failed\n",
				client->irq);
			goto err_standby;
		}
	}

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(&client->dev, "device_register failed\n");
		goto err_standby;
	}

	return 0;

err_standby:
	stk3310_set_state(data, STK3310_STATE_STANDBY);
	return ret;
}
