usbhsg_ep_queue(struct usb_ep *ep, struct usb_request *req,
			  gfp_t gfp_flags)
{
	struct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	struct usbhsg_gpriv *gpriv = usbhsg_uep_to_gpriv(uep);
	struct usbhsg_request *ureq = usbhsg_req_to_ureq(req);
	struct usbhs_pipe *pipe = usbhsg_uep_to_pipe(uep);


	if (usbhsg_is_not_connected(gpriv)	||
	    unlikely(!gpriv->driver)		||
	    unlikely(!pipe))
		return -ESHUTDOWN;

	usbhsg_queue_push(uep, ureq);

	return 0;
}
