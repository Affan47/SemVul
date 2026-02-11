pch_udc_pcd_ep_enable(struct usb_ep *usbep,
				    const struct usb_endpoint_descriptor *desc)
{
	struct pch_udc_ep	*ep;
	struct pch_udc_dev	*dev;
	unsigned long		iflags;

	if (!usbep || (usbep->name == ep0_string) || !desc ||
	    (desc->bDescriptorType != USB_DT_ENDPOINT) || !desc->wMaxPacketSize)
		return -EINVAL;

	ep = container_of(usbep, struct pch_udc_ep, ep);
	dev = ep->dev;
	if (!dev->driver || (dev->gadget.speed == USB_SPEED_UNKNOWN))
		return -ESHUTDOWN;
	spin_lock_irqsave(&dev->lock, iflags);
	ep->ep.desc = desc;
	ep->halted = 0;
	pch_udc_ep_enable(ep, &ep->dev->cfg_data, desc);
	ep->ep.maxpacket = usb_endpoint_maxp(desc);
	pch_udc_enable_ep_interrupts(ep->dev, PCH_UDC_EPINT(ep->in, ep->num));
	spin_unlock_irqrestore(&dev->lock, iflags);
	return 0;
}
