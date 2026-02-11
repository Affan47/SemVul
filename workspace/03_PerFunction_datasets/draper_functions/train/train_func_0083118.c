bcm2835_spi_handle_err(struct spi_master *master,
				   struct spi_message *msg)
{
	struct bcm2835_spi *bs = spi_master_get_devdata(master);


	if (bs->dma_pending) {
		dmaengine_terminate_all(master->dma_tx);
		dmaengine_terminate_all(master->dma_rx);
		bs->dma_pending = 0;
	}

	bcm2835_spi_reset_hw(master);
}
