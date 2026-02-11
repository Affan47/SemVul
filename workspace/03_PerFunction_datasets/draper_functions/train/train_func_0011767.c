usdhi6_dma_request(struct usdhi6_host *host, phys_addr_t start)
{
	struct dma_slave_config cfg = {
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
	};
	int ret;

	host->chan_tx = dma_request_slave_channel(mmc_dev(host->mmc), "tx");
	dev_dbg(mmc_dev(host->mmc), "%s: TX: got channel %p\n", __func__,
		host->chan_tx);

	if (!host->chan_tx)
		return;

	cfg.direction = DMA_MEM_TO_DEV;
	cfg.dst_addr = start + USDHI6_SD_BUF0;
	cfg.dst_maxburst = 128;
	cfg.src_addr = 0;
	ret = dmaengine_slave_config(host->chan_tx, &cfg);
	if (ret < 0)
		goto e_release_tx;

	host->chan_rx = dma_request_slave_channel(mmc_dev(host->mmc), "rx");
	dev_dbg(mmc_dev(host->mmc), "%s: RX: got channel %p\n", __func__,
		host->chan_rx);

	if (!host->chan_rx)
		goto e_release_tx;

	cfg.direction = DMA_DEV_TO_MEM;
	cfg.src_addr = cfg.dst_addr;
	cfg.src_maxburst = 128;
	cfg.dst_addr = 0;
	ret = dmaengine_slave_config(host->chan_rx, &cfg);
	if (ret < 0)
		goto e_release_rx;

	return;

e_release_rx:
	dma_release_channel(host->chan_rx);
	host->chan_rx = NULL;
e_release_tx:
	dma_release_channel(host->chan_tx);
	host->chan_tx = NULL;
}
