__spi_unmap_msg(struct spi_master *master, struct spi_message *msg)
{
	struct spi_transfer *xfer;
	struct device *tx_dev, *rx_dev;

	if (!master->cur_msg_mapped || !master->can_dma)
		return 0;

	if (master->dma_tx)
		tx_dev = master->dma_tx->device->dev;
	else
		tx_dev = &master->dev;

	if (master->dma_rx)
		rx_dev = master->dma_rx->device->dev;
	else
		rx_dev = &master->dev;

	list_for_each_entry(xfer, &msg->transfers, transfer_list) {
		if (!master->can_dma(master, msg->spi, xfer))
			continue;

		spi_unmap_buf(master, rx_dev, &xfer->rx_sg, DMA_FROM_DEVICE);
		spi_unmap_buf(master, tx_dev, &xfer->tx_sg, DMA_TO_DEVICE);
	}

	return 0;
}
