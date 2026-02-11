dma_sync_wait(struct dma_chan *chan, dma_cookie_t cookie)
{
	enum dma_status status;
	unsigned long dma_sync_wait_timeout = jiffies + msecs_to_jiffies(5000);

	dma_async_issue_pending(chan);
	do {
		status = dma_async_is_tx_complete(chan, cookie, NULL, NULL);
		if (time_after_eq(jiffies, dma_sync_wait_timeout)) {
			pr_err("%s: timeout!\n", __func__);
			return DMA_ERROR;
		}
		if (status != DMA_IN_PROGRESS)
			break;
		cpu_relax();
	} while (1);

	return status;
}
