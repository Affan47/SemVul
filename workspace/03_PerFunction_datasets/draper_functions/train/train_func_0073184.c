nbpf_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct nbpf_desc *desc = container_of(tx, struct nbpf_desc, async_tx);
	struct nbpf_channel *chan = desc->chan;
	unsigned long flags;
	dma_cookie_t cookie;

	spin_lock_irqsave(&chan->lock, flags);
	cookie = dma_cookie_assign(tx);
	list_add_tail(&desc->node, &chan->queued);
	spin_unlock_irqrestore(&chan->lock, flags);

	dev_dbg(chan->dma_chan.device->dev, "Entry %s(%d)\n", __func__, cookie);

	return cookie;
}
