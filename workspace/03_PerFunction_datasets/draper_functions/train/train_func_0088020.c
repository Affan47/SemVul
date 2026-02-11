dw_mci_suspend(struct dw_mci *host)
{
	if (host->use_dma && host->dma_ops->exit)
		host->dma_ops->exit(host);

	return 0;
}
