ak8975_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ak8975_data *data;
	struct iio_dev *indio_dev;
	int eoc_gpio;
	int err;
	const char *name = NULL;
	enum asahi_compass_chipset chipset = AK_MAX_TYPE;


	if (client->dev.platform_data)
		eoc_gpio = *(int *)(client->dev.platform_data);
	else if (client->dev.of_node)
		eoc_gpio = of_get_gpio(client->dev.of_node, 0);
	else
		eoc_gpio = -1;

	if (eoc_gpio == -EPROBE_DEFER)
		return -EPROBE_DEFER;


	if (gpio_is_valid(eoc_gpio)) {
		err = devm_gpio_request_one(&client->dev, eoc_gpio,
							GPIOF_IN, "ak_8975");
		if (err < 0) {
			dev_err(&client->dev,
				"failed to request GPIO %d, error %d\n",
							eoc_gpio, err);
			return err;
		}
	}


	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (indio_dev == NULL)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	data->client = client;
	data->eoc_gpio = eoc_gpio;
	data->eoc_irq = 0;


	if (id) {
		chipset = (enum asahi_compass_chipset)(id->driver_data);
		name = id->name;
	} else if (ACPI_HANDLE(&client->dev))
		name = ak8975_match_acpi_device(&client->dev, &chipset);
	else
		return -ENOSYS;

	if (chipset >= AK_MAX_TYPE) {
		dev_err(&client->dev, "AKM device type unsupported: %d\n",
			chipset);
		return -ENODEV;
	}

	data->def = &ak_def_array[chipset];
	err = ak8975_who_i_am(client, data->def->type);
	if (err < 0) {
		dev_err(&client->dev, "Unexpected device\n");
		return err;
	}
	dev_dbg(&client->dev, "Asahi compass chip %s\n", name);


	err = ak8975_setup(client);
	if (err < 0) {
		dev_err(&client->dev, "%s initialization fails\n", name);
		return err;
	}

	mutex_init(&data->lock);
	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = ak8975_channels;
	indio_dev->num_channels = ARRAY_SIZE(ak8975_channels);
	indio_dev->info = &ak8975_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->name = name;
	return devm_iio_device_register(&client->dev, indio_dev);
}
