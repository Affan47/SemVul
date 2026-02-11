usdhi6_dma_stop_unmap(struct usdhi6_host *host)
{
	struct mmc_data *data = host->mrq->data;

	if (!host->dma_active)
		return;

	usdhi6_write(host, USDHI6_CC_EXT_MODE, 0);
	host->dma_active = false;

	if (data->flags & MMC_DATA_READ)
		dma_unmap_sg(host->chan_rx->device->dev, data->sg,
			     data->sg_len, DMA_FROM_DEVICE);
	else
		dma_unmap_sg(host->chan_tx->device->dev, data->sg,
			     data->sg_len, DMA_TO_DEVICE);
}
