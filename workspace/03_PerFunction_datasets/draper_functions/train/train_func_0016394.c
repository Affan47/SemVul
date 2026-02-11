max1111_probe(struct spi_device *spi)
{
	enum chips chip = spi_get_device_id(spi)->driver_data;
	struct max1111_data *data;
	int err;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	err = spi_setup(spi);
	if (err < 0)
		return err;

	data = devm_kzalloc(&spi->dev, sizeof(struct max1111_data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	switch (chip) {
	case max1110:
		data->lsb = 8;
		data->sel_sh = MAX1110_CTRL_SEL_SH;
		break;
	case max1111:
		data->lsb = 8;
		data->sel_sh = MAX1111_CTRL_SEL_SH;
		break;
	case max1112:
		data->lsb = 16;
		data->sel_sh = MAX1110_CTRL_SEL_SH;
		break;
	case max1113:
		data->lsb = 16;
		data->sel_sh = MAX1111_CTRL_SEL_SH;
		break;
	}
	err = setup_transfer(data);
	if (err)
		return err;

	mutex_init(&data->drvdata_lock);

	data->spi = spi;
	spi_set_drvdata(spi, data);

	err = sysfs_create_group(&spi->dev.kobj, &max1111_attr_group);
	if (err) {
		dev_err(&spi->dev, "failed to create attribute group\n");
		return err;
	}
	if (chip == max1110 || chip == max1112) {
		err = sysfs_create_group(&spi->dev.kobj, &max1110_attr_group);
		if (err) {
			dev_err(&spi->dev,
				"failed to create extended attribute group\n");
			goto err_remove;
		}
	}

	data->hwmon_dev = hwmon_device_register(&spi->dev);
	if (IS_ERR(data->hwmon_dev)) {
		dev_err(&spi->dev, "failed to create hwmon device\n");
		err = PTR_ERR(data->hwmon_dev);
		goto err_remove;
	}

#ifdef CONFIG_SHARPSL_PM
	the_max1111 = data;
#endif
	return 0;

err_remove:
	sysfs_remove_group(&spi->dev.kobj, &max1110_attr_group);
	sysfs_remove_group(&spi->dev.kobj, &max1111_attr_group);
	return err;
}
