net2272_set_wedge(struct usb_ep *_ep)
{
	if (!_ep || _ep->name == ep0name)
		return -EINVAL;
	return net2272_set_halt_and_wedge(_ep, 1, 1);
}
