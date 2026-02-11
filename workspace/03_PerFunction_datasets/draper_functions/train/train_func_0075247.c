dw_dma_cyclic_free(struct dma_chan *chan)
{
	struct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	struct dw_dma		*dw = to_dw_dma(dwc->chan.device);
	struct dw_cyclic_desc	*cdesc = dwc->cdesc;
	int			i;
	unsigned long		flags;

	dev_dbg(chan2dev(&dwc->chan), "%s\n", __func__);

	if (!cdesc)
		return;

	spin_lock_irqsave(&dwc->lock, flags);

	dwc_chan_disable(dw, dwc);

	dma_writel(dw, CLEAR.BLOCK, dwc->mask);
	dma_writel(dw, CLEAR.ERROR, dwc->mask);
	dma_writel(dw, CLEAR.XFER, dwc->mask);

	spin_unlock_irqrestore(&dwc->lock, flags);

	for (i = 0; i < cdesc->periods; i++)
		dwc_desc_put(dwc, cdesc->desc[i]);

	kfree(cdesc->desc);
	kfree(cdesc);

	clear_bit(DW_DMA_IS_CYCLIC, &dwc->flags);
}
