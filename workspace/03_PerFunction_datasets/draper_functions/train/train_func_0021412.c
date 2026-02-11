cdns_spi_setup_transfer(struct spi_device *spi,
				   struct spi_transfer *transfer)
{
	struct cdns_spi *xspi = spi_master_get_devdata(spi->master);

	cdns_spi_config_clock_freq(spi, transfer);

	dev_dbg(&spi->dev, "%s, mode %d, %u bits/w, %u clock speed\n",
		__func__, spi->mode, spi->bits_per_word,
		xspi->speed_hz);

	return 0;
}
