ep_add_request(struct pxa_ep *ep, struct pxa27x_request *req)
{
	if (unlikely(!req))
		return;
	ep_vdbg(ep, "req:%p, lg=%d, udccsr=0x%03x\n", req,
		req->req.length, udc_ep_readl(ep, UDCCSR));

	req->in_use = 1;
	list_add_tail(&req->queue, &ep->queue);
	pio_irq_enable(ep);
}
