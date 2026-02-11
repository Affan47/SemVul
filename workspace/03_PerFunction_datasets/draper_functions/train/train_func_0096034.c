ad5064_probe(struct device *dev, enum ad5064_type type,
			const char *name, ad5064_write_func write)
{
	struct iio_dev *indio_dev;
	struct ad5064_state *st;
	unsigned int midscale;
	unsigned int i;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*st));
	if (indio_dev == NULL)
		return  -ENOMEM;

	st = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	st->chip_info = &ad5064_chip_info_tbl[type];
	st->dev = dev;
	st->write = write;

	for (i = 0; i < ad5064_num_vref(st); ++i)
		st->vref_reg[i].supply = ad5064_vref_name(st, i);

	ret = devm_regulator_bulk_get(dev, ad5064_num_vref(st),
		st->vref_reg);
	if (ret) {
		if (!st->chip_info->internal_vref)
			return ret;
		st->use_internal_vref = true;
		ret = ad5064_write(st, AD5064_CMD_CONFIG, 0,
			AD5064_CONFIG_INT_VREF_ENABLE, 0);
		if (ret) {
			dev_err(dev, "Failed to enable internal vref: %d\n",
				ret);
			return ret;
		}
	} else {
		ret = regulator_bulk_enable(ad5064_num_vref(st), st->vref_reg);
		if (ret)
			return ret;
	}

	indio_dev->dev.parent = dev;
	indio_dev->name = name;
	indio_dev->info = &ad5064_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;

	midscale = (1 << indio_dev->channels[0].scan_type.realbits) /  2;

	for (i = 0; i < st->chip_info->num_channels; ++i) {
		st->pwr_down_mode[i] = AD5064_LDAC_PWRDN_1K;
		st->dac_cache[i] = midscale;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_disable_reg;

	return 0;

error_disable_reg:
	if (!st->use_internal_vref)
		regulator_bulk_disable(ad5064_num_vref(st), st->vref_reg);

	return ret;
}
