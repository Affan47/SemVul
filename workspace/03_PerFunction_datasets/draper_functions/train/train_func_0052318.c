wbsd_release_dma(struct wbsd_host *host)
{
	if (host->dma_addr) {
		dma_unmap_single(mmc_dev(host->mmc), host->dma_addr,
			WBSD_DMA_SIZE, DMA_BIDIRECTIONAL);
	}
	kfree(host->dma_buffer);
	if (host->dma >= 0)
		free_dma(host->dma);

	host->dma = -1;
	host->dma_buffer = NULL;
	host->dma_addr = 0;
}
