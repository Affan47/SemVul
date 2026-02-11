vgg2432a4_probe(struct spi_device *spi)
{
	int ret;

	ret = ili9320_probe_spi(spi, &vgg2432a4_client);
	if (ret != 0) {
		dev_err(&spi->dev, "failed to initialise ili9320\n");
		return ret;
	}

	return 0;
}
