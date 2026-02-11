sh_mmcif_request_dma(struct sh_mmcif_host *host)
{
	struct device *dev = sh_mmcif_host_to_dev(host);
	host->dma_active = false;


	if (IS_ENABLED(CONFIG_SUPERH) && dev->platform_data) {
		struct sh_mmcif_plat_data *pdata = dev->platform_data;

		host->chan_tx = sh_mmcif_request_dma_pdata(host,
							pdata->slave_id_tx);
		host->chan_rx = sh_mmcif_request_dma_pdata(host,
							pdata->slave_id_rx);
	} else {
		host->chan_tx = dma_request_slave_channel(dev, "tx");
		host->chan_rx = dma_request_slave_channel(dev, "rx");
	}
	dev_dbg(dev, "%s: got channel TX %p RX %p\n", __func__, host->chan_tx,
		host->chan_rx);

	if (!host->chan_tx || !host->chan_rx ||
	    sh_mmcif_dma_slave_config(host, host->chan_tx, DMA_MEM_TO_DEV) ||
	    sh_mmcif_dma_slave_config(host, host->chan_rx, DMA_DEV_TO_MEM))
		goto error;

	return;

error:
	if (host->chan_tx)
		dma_release_channel(host->chan_tx);
	if (host->chan_rx)
		dma_release_channel(host->chan_rx);
	host->chan_tx = host->chan_rx = NULL;
}
