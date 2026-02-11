usb_gadget_giveback_request(struct usb_ep *ep,
		struct usb_request *req)
{
	if (likely(req->status == 0))
		usb_led_activity(USB_LED_EVENT_GADGET);

	req->complete(ep, req);
}
