s5c73m3_spi_probe(struct spi_device *spi)
{
	int r;
	struct s5c73m3 *state = container_of(spi->dev.driver, struct s5c73m3,
					     spidrv.driver);
	spi->bits_per_word = 32;

	r = spi_setup(spi);
	if (r < 0) {
		dev_err(&spi->dev, "spi_setup() failed\n");
		return r;
	}

	mutex_lock(&state->lock);
	state->spi_dev = spi;
	mutex_unlock(&state->lock);

	v4l2_info(&state->sensor_sd, "S5C73M3 SPI probed successfully\n");
	return 0;
}
