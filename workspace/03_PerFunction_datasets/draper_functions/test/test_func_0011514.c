bcm2835_dma_release(struct spi_master *master)
{
	if (master->dma_tx) {
		dmaengine_terminate_all(master->dma_tx);
		dma_release_channel(master->dma_tx);
		master->dma_tx = NULL;
	}
	if (master->dma_rx) {
		dmaengine_terminate_all(master->dma_rx);
		dma_release_channel(master->dma_rx);
		master->dma_rx = NULL;
	}
}
