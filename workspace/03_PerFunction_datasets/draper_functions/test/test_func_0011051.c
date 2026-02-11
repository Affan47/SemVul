l4f00242t03_lcd_powerdown(struct spi_device *spi)
{
	struct l4f00242t03_pdata *pdata = dev_get_platdata(&spi->dev);
	struct l4f00242t03_priv *priv = spi_get_drvdata(spi);

	dev_dbg(&spi->dev, "Powering down LCD\n");

	gpio_set_value(pdata->data_enable_gpio, 0);

	regulator_disable(priv->io_reg);
	regulator_disable(priv->core_reg);
}
