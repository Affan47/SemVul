sc18is602_setup(struct spi_device *spi)
{
	struct sc18is602 *hw = spi_master_get_devdata(spi->master);


	if (hw->id == sc18is602 && spi->chip_select == 2)
		return -ENXIO;

	return 0;
}
