usbhsg_ep_free_request(struct usb_ep *ep,
				   struct usb_request *req)
{
	struct usbhsg_request *ureq = usbhsg_req_to_ureq(req);

	WARN_ON(!list_empty(&ureq->pkt.node));
	kfree(ureq);
}
