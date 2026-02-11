ad7606_spi_read_block(struct device *dev,
				 int count, void *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	int i, ret;
	unsigned short *data = buf;

	ret = spi_read(spi, buf, count * 2);
	if (ret < 0) {
		dev_err(&spi->dev, "SPI read error\n");
		return ret;
	}

	for (i = 0; i < count; i++)
		data[i] = be16_to_cpu(data[i]);

	return 0;
}
