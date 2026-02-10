dwc_handle_cyclic(struct dw_dma *dw, struct dw_dma_chan *dwc,
		u32 status_block, u32 status_err, u32 status_xfer)
{
	unsigned long flags;

	if (status_block & dwc->mask) {
		void (*callback)(void *param);
		void *callback_param;

		dev_vdbg(chan2dev(&dwc->chan), "new cyclic period llp 0x%08x\n",
				channel_readl(dwc, LLP));
		dma_writel(dw, CLEAR.BLOCK, dwc->mask);

		callback = dwc->cdesc->period_callback;
		callback_param = dwc->cdesc->period_callback_param;

		if (callback)
			callback(callback_param);
	}


	if (unlikely(status_err & dwc->mask) ||
			unlikely(status_xfer & dwc->mask)) {
		int i;

		dev_err(chan2dev(&dwc->chan),
			"cyclic DMA unexpected %s interrupt, stopping DMA transfer\n",
			status_xfer ? "xfer" : "error");

		spin_lock_irqsave(&dwc->lock, flags);

		dwc_dump_chan_regs(dwc);

		dwc_chan_disable(dw, dwc);


		channel_writel(dwc, LLP, 0);
		channel_writel(dwc, CTL_LO, 0);
		channel_writel(dwc, CTL_HI, 0);

		dma_writel(dw, CLEAR.BLOCK, dwc->mask);
		dma_writel(dw, CLEAR.ERROR, dwc->mask);
		dma_writel(dw, CLEAR.XFER, dwc->mask);

		for (i = 0; i < dwc->cdesc->periods; i++)
			dwc_dump_lli(dwc, &dwc->cdesc->desc[i]->lli);

		spin_unlock_irqrestore(&dwc->lock, flags);
	}


	channel_set_bit(dw, MASK.BLOCK, dwc->mask);
}
