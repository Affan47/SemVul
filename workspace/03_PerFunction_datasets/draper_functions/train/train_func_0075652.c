dma_advance(struct goku_udc *dev, struct goku_ep *ep)
{
	struct goku_request		*req;
	struct goku_udc_regs __iomem	*regs = ep->dev->regs;
	u32				master;

	master = readl(&regs->dma_master);

	if (unlikely(list_empty(&ep->queue))) {
stop:
		if (ep->is_in)
			dev->int_enable &= ~INT_MSTRDEND;
		else
			dev->int_enable &= ~(INT_MSTWREND|INT_MSTWRTMOUT);
		writel(dev->int_enable, &regs->int_enable);
		return;
	}
	req = list_entry(ep->queue.next, struct goku_request, queue);


	if (likely(ep->is_in)) {
		if (unlikely(master & MST_RD_ENA))
			return;
		req->req.actual = readl(&regs->in_dma_current);
	} else {
		if (unlikely(master & MST_WR_ENA))
			return;


		req->req.actual = readl(&regs->out_dma_current);
	}
	req->req.actual -= req->req.dma;
	req->req.actual++;

#ifdef USB_TRACE
	VDBG(dev, "done %s %s dma, %u/%u bytes, req %p\n",
		ep->ep.name, ep->is_in ? "IN" : "OUT",
		req->req.actual, req->req.length, req);
#endif
	done(ep, req, 0);
	if (list_empty(&ep->queue))
		goto stop;
	req = list_entry(ep->queue.next, struct goku_request, queue);
	(void) start_dma(ep, req);
}
