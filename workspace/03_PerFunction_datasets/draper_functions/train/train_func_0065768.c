lms501kf03_probe(struct spi_device *spi)
{
	struct lms501kf03 *lcd = NULL;
	struct lcd_device *ld = NULL;
	int ret = 0;

	lcd = devm_kzalloc(&spi->dev, sizeof(struct lms501kf03), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;


	spi->bits_per_word = 9;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "spi setup failed.\n");
		return ret;
	}

	lcd->spi = spi;
	lcd->dev = &spi->dev;

	lcd->lcd_pd = dev_get_platdata(&spi->dev);
	if (!lcd->lcd_pd) {
		dev_err(&spi->dev, "platform data is NULL\n");
		return -EINVAL;
	}

	ld = devm_lcd_device_register(&spi->dev, "lms501kf03", &spi->dev, lcd,
					&lms501kf03_lcd_ops);
	if (IS_ERR(ld))
		return PTR_ERR(ld);

	lcd->ld = ld;

	if (!lcd->lcd_pd->lcd_enabled) {


		lcd->power = FB_BLANK_POWERDOWN;

		lms501kf03_power(lcd, FB_BLANK_UNBLANK);
	} else {
		lcd->power = FB_BLANK_UNBLANK;
	}

	spi_set_drvdata(spi, lcd);

	dev_info(&spi->dev, "lms501kf03 panel driver has been probed.\n");

	return 0;
}
