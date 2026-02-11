linux_to_wlan(wilc_wlan_inp_t *nwi, struct wilc *nic)
{

	PRINT_D(INIT_DBG, "Linux to Wlan services ...\n");

	nwi->os_context.os_private = (void *)nic;

#ifdef WILC_SDIO
	nwi->io_func.io_type = HIF_SDIO;
	nwi->io_func.io_init = linux_sdio_init;
	nwi->io_func.io_deinit = linux_sdio_deinit;
	nwi->io_func.u.sdio.sdio_cmd52 = linux_sdio_cmd52;
	nwi->io_func.u.sdio.sdio_cmd53 = linux_sdio_cmd53;
	nwi->io_func.u.sdio.sdio_set_max_speed = linux_sdio_set_max_speed;
	nwi->io_func.u.sdio.sdio_set_default_speed = linux_sdio_set_default_speed;
#else
	nwi->io_func.io_type = HIF_SPI;
	nwi->io_func.io_init = linux_spi_init;
	nwi->io_func.io_deinit = linux_spi_deinit;
	nwi->io_func.u.spi.spi_tx = linux_spi_write;
	nwi->io_func.u.spi.spi_rx = linux_spi_read;
	nwi->io_func.u.spi.spi_trx = linux_spi_write_read;
	nwi->io_func.u.spi.spi_max_speed = linux_spi_set_max_speed;
#endif
}
