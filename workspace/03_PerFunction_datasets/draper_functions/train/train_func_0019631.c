abort_dma(struct goku_ep *ep, int status)
{
	struct goku_udc_regs __iomem	*regs = ep->dev->regs;
	struct goku_request		*req;
	u32				curr, master;


	command(regs, COMMAND_FIFO_DISABLE, ep->num);
	req = list_entry(ep->queue.next, struct goku_request, queue);
	master = readl(&regs->dma_master) & MST_RW_BITS;


	if (ep->is_in) {
		if (unlikely((readl(&regs->dma_master) & MST_RD_ENA) == 0))
			goto finished;
		curr = readl(&regs->in_dma_current);

		writel(curr, &regs->in_dma_end);
		writel(curr, &regs->in_dma_start);

		master &= ~MST_R_BITS;
		master |= MST_RD_RESET;
		writel(master, &regs->dma_master);

		if (readl(&regs->dma_master) & MST_RD_ENA)
			DBG(ep->dev, "IN dma active after reset!\n");

	} else {
		if (unlikely((readl(&regs->dma_master) & MST_WR_ENA) == 0))
			goto finished;
		curr = readl(&regs->out_dma_current);

		writel(curr, &regs->out_dma_end);
		writel(curr, &regs->out_dma_start);

		master &= ~MST_W_BITS;
		master |= MST_WR_RESET;
		writel(master, &regs->dma_master);

		if (readl(&regs->dma_master) & MST_WR_ENA)
			DBG(ep->dev, "OUT dma active after reset!\n");
	}
	req->req.actual = (curr - req->req.dma) + 1;
	req->req.status = status;

	VDBG(ep->dev, "%s %s %s %d/%d\n", __func__, ep->ep.name,
		ep->is_in ? "IN" : "OUT",
		req->req.actual, req->req.length);

	command(regs, COMMAND_FIFO_ENABLE, ep->num);

	return;

finished:

	command(regs, COMMAND_FIFO_ENABLE, ep->num);
	req->req.actual = req->req.length;
	req->req.status = 0;
}
