gr_ep_disable(struct usb_ep *_ep)
{
	struct gr_ep *ep;
	struct gr_udc *dev;
	unsigned long flags;

	ep = container_of(_ep, struct gr_ep, ep);
	if (!_ep || !ep->ep.desc)
		return -ENODEV;

	dev = ep->dev;


	if (ep == &dev->epo[0] || ep == &dev->epi[0])
		return -EINVAL;

	if (dev->ep0state == GR_EP0_SUSPEND)
		return -EBUSY;

	dev_dbg(ep->dev->dev, "EP: disable %s\n", ep->ep.name);

	spin_lock_irqsave(&dev->lock, flags);

	gr_ep_nuke(ep);
	gr_ep_reset(ep);
	ep->ep.desc = NULL;

	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}
