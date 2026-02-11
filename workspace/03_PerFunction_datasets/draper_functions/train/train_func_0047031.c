td_tx_status(struct dma_chan *chan, dma_cookie_t cookie,
				    struct dma_tx_state *txstate)
{
	enum dma_status ret;

	dev_dbg(chan2dev(chan), "%s: Entry\n", __func__);

	ret = dma_cookie_status(chan, cookie, txstate);

	dev_dbg(chan2dev(chan), "%s: exit, ret: %d\n", 	__func__, ret);

	return ret;
}
