fsl_spi_cleanup(struct spi_device *spi)
{
	struct mpc8xxx_spi *mpc8xxx_spi = spi_master_get_devdata(spi->master);
	struct spi_mpc8xxx_cs *cs = spi_get_ctldata(spi);

	if (mpc8xxx_spi->type == TYPE_GRLIB && gpio_is_valid(spi->cs_gpio))
		gpio_free(spi->cs_gpio);

	kfree(cs);
	spi_set_ctldata(spi, NULL);
}
