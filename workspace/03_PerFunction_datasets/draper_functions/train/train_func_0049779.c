rspi_dma_check_then_transfer(struct rspi_data *rspi,
					 struct spi_transfer *xfer)
{
	if (!rspi->master->can_dma || !__rspi_can_dma(rspi, xfer))
		return -EAGAIN;


	return rspi_dma_transfer(rspi, &xfer->tx_sg,
				xfer->rx_buf ? &xfer->rx_sg : NULL);
}
