composite_setup_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct usb_composite_dev *cdev;

	if (req->status || req->actual != req->length)
		DBG((struct usb_composite_dev *) ep->driver_data,
				"setup complete --> %d, %d/%d\n",
				req->status, req->actual, req->length);


	if (!req->context)
		return;

	cdev = req->context;

	if (cdev->req == req)
		cdev->setup_pending = false;
	else if (cdev->os_desc_req == req)
		cdev->os_desc_pending = false;
	else
		WARN(1, "unknown request %p\n", req);
}
