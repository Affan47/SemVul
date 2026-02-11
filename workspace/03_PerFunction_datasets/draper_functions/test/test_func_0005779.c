ds1343_probe(struct spi_device *spi)
{
	struct ds1343_priv *priv;
	struct regmap_config config;
	unsigned int data;
	int res;

	memset(&config, 0, sizeof(config));
	config.reg_bits = 8;
	config.val_bits = 8;
	config.write_flag_mask = 0x80;

	priv = devm_kzalloc(&spi->dev, sizeof(struct ds1343_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->spi = spi;
	mutex_init(&priv->mutex);


	spi->mode = SPI_MODE_3 | SPI_CS_HIGH;
	spi->bits_per_word = 8;
	res = spi_setup(spi);
	if (res)
		return res;

	spi_set_drvdata(spi, priv);

	priv->map = devm_regmap_init_spi(spi, &config);

	if (IS_ERR(priv->map)) {
		dev_err(&spi->dev, "spi regmap init failed for rtc ds1343\n");
		return PTR_ERR(priv->map);
	}

	res = regmap_read(priv->map, DS1343_SECONDS_REG, &data);
	if (res)
		return res;

	regmap_read(priv->map, DS1343_CONTROL_REG, &data);
	data |= DS1343_INTCN;
	data &= ~(DS1343_EOSC | DS1343_A1IE | DS1343_A0IE);
	regmap_write(priv->map, DS1343_CONTROL_REG, data);

	regmap_read(priv->map, DS1343_STATUS_REG, &data);
	data &= ~(DS1343_OSF | DS1343_IRQF1 | DS1343_IRQF0);
	regmap_write(priv->map, DS1343_STATUS_REG, data);

	priv->rtc = devm_rtc_device_register(&spi->dev, "ds1343",
					&ds1343_rtc_ops, THIS_MODULE);
	if (IS_ERR(priv->rtc)) {
		dev_err(&spi->dev, "unable to register rtc ds1343\n");
		return PTR_ERR(priv->rtc);
	}

	priv->irq = spi->irq;

	if (priv->irq >= 0) {
		res = devm_request_threaded_irq(&spi->dev, spi->irq, NULL,
						ds1343_thread, IRQF_ONESHOT,
						"ds1343", priv);
		if (res) {
			priv->irq = -1;
			dev_err(&spi->dev,
				"unable to request irq for rtc ds1343\n");
		} else {
			device_init_wakeup(&spi->dev, true);
			dev_pm_set_wake_irq(&spi->dev, spi->irq);
		}
	}

	res = ds1343_sysfs_register(&spi->dev);
	if (res)
		dev_err(&spi->dev,
			"unable to create sysfs entries for rtc ds1343\n");

	return 0;
}
