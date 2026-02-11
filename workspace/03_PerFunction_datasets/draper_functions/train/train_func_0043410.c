xlp_spi_interrupt(int irq, void *dev_id)
{
	struct xlp_spi_priv *xspi = dev_id;
	u32 stat;

	stat = xlp_spi_reg_read(xspi, xspi->cs, XLP_SPI_STATUS) &
		XLP_SPI_STAT_MASK;
	if (!stat)
		return IRQ_NONE;

	if (stat & XLP_SPI_TX_INT) {
		if (xspi->tx_len)
			xlp_spi_fill_txfifo(xspi);
		if (stat & XLP_SPI_TX_UF)
			xspi->txerrors++;
	}

	if (stat & XLP_SPI_RX_INT) {
		if (xspi->rx_len)
			xlp_spi_read_rxfifo(xspi);
		if (stat & XLP_SPI_RX_OF)
			xspi->rxerrors++;
	}


	xlp_spi_reg_write(xspi, xspi->cs, XLP_SPI_STATUS, stat);
	if (stat & XLP_SPI_XFR_DONE)
		complete(&xspi->done);

	return IRQ_HANDLED;
}
