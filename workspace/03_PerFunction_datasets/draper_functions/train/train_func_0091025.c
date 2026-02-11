wbsd_request_dma(struct wbsd_host *host, int dma)
{
	if (dma < 0)
		return;

	if (request_dma(dma, DRIVER_NAME))
		goto err;


	host->dma_buffer = kmalloc(WBSD_DMA_SIZE,
		GFP_NOIO | GFP_DMA | __GFP_REPEAT | __GFP_NOWARN);
	if (!host->dma_buffer)
		goto free;


	host->dma_addr = dma_map_single(mmc_dev(host->mmc), host->dma_buffer,
		WBSD_DMA_SIZE, DMA_BIDIRECTIONAL);


	if ((host->dma_addr & 0xffff) != 0)
		goto kfree;


	else if (host->dma_addr >= 0x1000000)
		goto kfree;

	host->dma = dma;

	return;

kfree:


	BUG_ON(1);

	dma_unmap_single(mmc_dev(host->mmc), host->dma_addr,
		WBSD_DMA_SIZE, DMA_BIDIRECTIONAL);
	host->dma_addr = 0;

	kfree(host->dma_buffer);
	host->dma_buffer = NULL;

free:
	free_dma(dma);

err:
	pr_warn(DRIVER_NAME ": Unable to allocate DMA %d - falling back on FIFO\n",
		dma);
}
