pdc_chain_complete(struct pch_dma_chan *pd_chan,
			       struct pch_dma_desc *desc)
{
	struct dma_async_tx_descriptor *txd = &desc->txd;
	dma_async_tx_callback callback = txd->callback;
	void *param = txd->callback_param;

	list_splice_init(&desc->tx_list, &pd_chan->free_list);
	list_move(&desc->desc_node, &pd_chan->free_list);

	if (callback)
		callback(param);
}
