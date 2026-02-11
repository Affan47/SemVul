zynqmp_qspi_setup(struct spi_device *qspi)
{
	if (qspi->master->busy)
		return -EBUSY;
	return 0;
}
