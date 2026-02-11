tsl2563_probe(struct i2c_client *client,
				const struct i2c_device_id *device_id)
{
	struct iio_dev *indio_dev;
	struct tsl2563_chip *chip;
	struct tsl2563_platform_data *pdata = client->dev.platform_data;
	struct device_node *np = client->dev.of_node;
	int err = 0;
	u8 id = 0;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;

	chip = iio_priv(indio_dev);

	i2c_set_clientdata(client, chip);
	chip->client = client;

	err = tsl2563_detect(chip);
	if (err) {
		dev_err(&client->dev, "detect error %d\n", -err);
		return err;
	}

	err = tsl2563_read_id(chip, &id);
	if (err) {
		dev_err(&client->dev, "read id error %d\n", -err);
		return err;
	}

	mutex_init(&chip->lock);


	chip->low_thres = 0x0;
	chip->high_thres = 0xffff;
	chip->gainlevel = tsl2563_gainlevel_table;
	chip->intr = TSL2563_INT_PERSIST(4);
	chip->calib0 = tsl2563_calib_from_sysfs(CALIB_BASE_SYSFS);
	chip->calib1 = tsl2563_calib_from_sysfs(CALIB_BASE_SYSFS);

	if (pdata)
		chip->cover_comp_gain = pdata->cover_comp_gain;
	else if (np)
		of_property_read_u32(np, "amstaos,cover-comp-gain",
				     &chip->cover_comp_gain);
	else
		chip->cover_comp_gain = 1;

	dev_info(&client->dev, "model %d, rev. %d\n", id >> 4, id & 0x0f);
	indio_dev->name = client->name;
	indio_dev->channels = tsl2563_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsl2563_channels);
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (client->irq)
		indio_dev->info = &tsl2563_info;
	else
		indio_dev->info = &tsl2563_info_no_irq;

	if (client->irq) {
		err = devm_request_threaded_irq(&client->dev, client->irq,
					   NULL,
					   &tsl2563_event_handler,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   "tsl2563_event",
					   indio_dev);
		if (err) {
			dev_err(&client->dev, "irq request error %d\n", -err);
			return err;
		}
	}

	err = tsl2563_configure(chip);
	if (err) {
		dev_err(&client->dev, "configure error %d\n", -err);
		return err;
	}

	INIT_DELAYED_WORK(&chip->poweroff_work, tsl2563_poweroff_work);


	schedule_delayed_work(&chip->poweroff_work, 5 * HZ);

	err = iio_device_register(indio_dev);
	if (err) {
		dev_err(&client->dev, "iio registration error %d\n", -err);
		goto fail;
	}

	return 0;

fail:
	cancel_delayed_work(&chip->poweroff_work);
	flush_scheduled_work();
	return err;
}
