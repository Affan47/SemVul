restart_dma(struct net2280_ep *ep)
{
	struct net2280_request	*req;

	if (ep->stopped)
		return;
	req = list_entry(ep->queue.next, struct net2280_request, queue);

	start_dma(ep, req);
}
