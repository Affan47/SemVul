pxa_ep_fifo_flush(struct usb_ep *_ep)
{
	struct pxa_ep		*ep;
	struct udc_usb_ep	*udc_usb_ep;
	unsigned long		flags;

	if (!_ep)
		return;
	udc_usb_ep = container_of(_ep, struct udc_usb_ep, usb_ep);
	ep = udc_usb_ep->pxa_ep;
	if (!ep || is_ep0(ep))
		return;

	spin_lock_irqsave(&ep->lock, flags);

	if (unlikely(!list_empty(&ep->queue)))
		ep_dbg(ep, "called while queue list not empty\n");
	ep_dbg(ep, "called\n");


	if (!ep->dir_in) {
		while (!ep_is_empty(ep))
			udc_ep_readl(ep, UDCDR);
	} else {

		ep_write_UDCCSR(ep,
				UDCCSR_PC | UDCCSR_FEF | UDCCSR_TRN
				| (EPXFERTYPE_is_ISO(ep) ? 0 : UDCCSR_SST));
	}

	spin_unlock_irqrestore(&ep->lock, flags);
}
