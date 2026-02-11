goku_free_request(struct usb_ep *_ep, struct usb_request *_req)
{
	struct goku_request	*req;

	if (!_ep || !_req)
		return;

	req = container_of(_req, struct goku_request, req);
	WARN_ON(!list_empty(&req->queue));
	kfree(req);
}
