modalias_show(struct device *dev, struct device_attribute *a, char *buf)
{
	const struct spi_device	*spi = to_spi_device(dev);
	int len;

	len = acpi_device_modalias(dev, buf, PAGE_SIZE - 1);
	if (len != -ENODEV)
		return len;

	return sprintf(buf, "%s%s\n", SPI_MODULE_PREFIX, spi->modalias);
}
