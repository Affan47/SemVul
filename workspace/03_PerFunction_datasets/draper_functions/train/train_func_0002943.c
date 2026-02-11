pxa27x_change_interface(struct pxa_udc *udc, int iface, int alt)
{
	struct usb_ctrlrequest  req;

	dev_dbg(udc->dev, "interface=%d, alternate setting=%d\n", iface, alt);

	udc->last_interface = iface;
	udc->last_alternate = alt;

	req.bRequestType = USB_RECIP_INTERFACE;
	req.bRequest = USB_REQ_SET_INTERFACE;
	req.wValue = alt;
	req.wIndex = iface;
	req.wLength = 0;

	set_ep0state(udc, WAIT_ACK_SET_CONF_INTERF);
	udc->driver->setup(&udc->gadget, &req);
	ep_write_UDCCSR(&udc->pxa_ep[0], UDCCSR0_AREN);
}
