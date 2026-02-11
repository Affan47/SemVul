gr_handle_in_ep(struct gr_ep *ep)
{
	struct gr_request *req;

	req = list_first_entry(&ep->queue, struct gr_request, queue);
	if (!req->last_desc)
		return 0;

	if (ACCESS_ONCE(req->last_desc->ctrl) & GR_DESC_IN_CTRL_EN)
		return 0;

	if (gr_read32(&ep->regs->epstat) & (GR_EPSTAT_B1 | GR_EPSTAT_B0))
		return 0;


	gr_dma_advance(ep, 0);

	return 1;
}
