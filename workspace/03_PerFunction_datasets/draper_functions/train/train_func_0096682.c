ds3234_probe(struct spi_device *spi)
{
	struct rtc_device *rtc;
	unsigned char tmp;
	int res;

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	res = ds3234_get_reg(&spi->dev, DS3234_REG_SECONDS, &tmp);
	if (res != 0)
		return res;


	ds3234_get_reg(&spi->dev, DS3234_REG_CONTROL, &tmp);
	ds3234_set_reg(&spi->dev, DS3234_REG_CONTROL, tmp & 0x1c);

	ds3234_get_reg(&spi->dev, DS3234_REG_CONT_STAT, &tmp);
	ds3234_set_reg(&spi->dev, DS3234_REG_CONT_STAT, tmp & 0x88);


	ds3234_get_reg(&spi->dev, DS3234_REG_CONTROL, &tmp);
	dev_info(&spi->dev, "Control Reg: 0x%02x\n", tmp);

	ds3234_get_reg(&spi->dev, DS3234_REG_CONT_STAT, &tmp);
	dev_info(&spi->dev, "Ctrl/Stat Reg: 0x%02x\n", tmp);

	rtc = devm_rtc_device_register(&spi->dev, "ds3234",
				&ds3234_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	spi_set_drvdata(spi, rtc);

	return 0;
}
