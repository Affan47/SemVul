img_spfi_prepare(struct spi_master *master, struct spi_message *msg)
{
	struct img_spfi *spfi = spi_master_get_devdata(master);
	u32 val;

	val = spfi_readl(spfi, SPFI_PORT_STATE);
	if (msg->spi->mode & SPI_CPHA)
		val |= SPFI_PORT_STATE_CK_PHASE(msg->spi->chip_select);
	else
		val &= ~SPFI_PORT_STATE_CK_PHASE(msg->spi->chip_select);
	if (msg->spi->mode & SPI_CPOL)
		val |= SPFI_PORT_STATE_CK_POL(msg->spi->chip_select);
	else
		val &= ~SPFI_PORT_STATE_CK_POL(msg->spi->chip_select);
	spfi_writel(spfi, val, SPFI_PORT_STATE);

	return 0;
}
