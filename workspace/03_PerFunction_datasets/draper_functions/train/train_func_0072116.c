fotg210_in_fifo_handler(struct fotg210_ep *ep)
{
	struct fotg210_request *req = list_entry(ep->queue.next,
					struct fotg210_request, queue);

	if (req->req.length)
		fotg210_start_dma(ep, req);
	fotg210_done(ep, req, 0);
}
