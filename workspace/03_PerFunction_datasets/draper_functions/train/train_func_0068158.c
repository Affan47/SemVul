nuke(struct dummy *dum, struct dummy_ep *ep)
{
	while (!list_empty(&ep->queue)) {
		struct dummy_request	*req;

		req = list_entry(ep->queue.next, struct dummy_request, queue);
		list_del_init(&req->queue);
		req->req.status = -ESHUTDOWN;

		spin_unlock(&dum->lock);
		usb_gadget_giveback_request(&ep->ep, &req->req);
		spin_lock(&dum->lock);
	}
}
