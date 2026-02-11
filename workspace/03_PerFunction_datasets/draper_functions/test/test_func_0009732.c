dma_run_dependencies(struct dma_async_tx_descriptor *tx)
{
	struct dma_async_tx_descriptor *dep = txd_next(tx);
	struct dma_async_tx_descriptor *dep_next;
	struct dma_chan *chan;

	if (!dep)
		return;


	txd_clear_next(tx);
	chan = dep->chan;


	for (; dep; dep = dep_next) {
		txd_lock(dep);
		txd_clear_parent(dep);
		dep_next = txd_next(dep);
		if (dep_next && dep_next->chan == chan)
			txd_clear_next(dep);
		else
			dep_next = NULL;
		txd_unlock(dep);

		dep->tx_submit(dep);
	}

	chan->device->device_issue_pending(chan);
}
