dummy_alloc_request(struct usb_ep *_ep,
		gfp_t mem_flags)
{
	struct dummy_ep		*ep;
	struct dummy_request	*req;

	if (!_ep)
		return NULL;
	ep = usb_ep_to_dummy_ep(_ep);

	req = kzalloc(sizeof(*req), mem_flags);
	if (!req)
		return NULL;
	INIT_LIST_HEAD(&req->queue);
	return &req->req;
}
