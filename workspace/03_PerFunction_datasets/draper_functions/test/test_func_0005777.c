apds9960_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct apds9960_data *data;
	struct iio_buffer *buffer;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	buffer = devm_iio_kfifo_allocate(&client->dev);
	if (!buffer)
		return -ENOMEM;

	iio_device_attach_buffer(indio_dev, buffer);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &apds9960_info;
	indio_dev->name = APDS9960_DRV_NAME;
	indio_dev->channels = apds9960_channels;
	indio_dev->num_channels = ARRAY_SIZE(apds9960_channels);
	indio_dev->available_scan_masks = apds9960_scan_masks;
	indio_dev->modes = (INDIO_BUFFER_SOFTWARE | INDIO_DIRECT_MODE);
	indio_dev->setup_ops = &apds9960_buffer_setup_ops;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	data->regmap = devm_regmap_init_i2c(client, &apds9960_regmap_config);
	if (IS_ERR(data->regmap)) {
		dev_err(&client->dev, "regmap initialization failed.\n");
		return PTR_ERR(data->regmap);
	}

	data->client = client;
	data->indio_dev = indio_dev;
	mutex_init(&data->lock);

	ret = pm_runtime_set_active(&client->dev);
	if (ret)
		goto error_power_down;

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, 5000);
	pm_runtime_use_autosuspend(&client->dev);

	apds9960_set_power_state(data, true);

	ret = apds9960_regfield_init(data);
	if (ret)
		goto error_power_down;

	ret = apds9960_chip_init(data);
	if (ret)
		goto error_power_down;

	if (client->irq <= 0) {
		dev_err(&client->dev, "no valid irq defined\n");
		ret = -EINVAL;
		goto error_power_down;
	}
	ret = devm_request_threaded_irq(&client->dev, client->irq,
					NULL, apds9960_interrupt_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"apds9960_event",
					indio_dev);
	if (ret) {
		dev_err(&client->dev, "request irq (%d) failed\n", client->irq);
		goto error_power_down;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_power_down;

	apds9960_set_power_state(data, false);

	return 0;

error_power_down:
	apds9960_set_power_state(data, false);

	return ret;
}
