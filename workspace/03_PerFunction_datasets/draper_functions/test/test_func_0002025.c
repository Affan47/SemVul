musb_h_disable(struct usb_hcd *hcd, struct usb_host_endpoint *hep)
{
	u8			is_in = hep->desc.bEndpointAddress & USB_DIR_IN;
	unsigned long		flags;
	struct musb		*musb = hcd_to_musb(hcd);
	struct musb_qh		*qh;
	struct urb		*urb;

	spin_lock_irqsave(&musb->lock, flags);

	qh = hep->hcpriv;
	if (qh == NULL)
		goto exit;


	qh->is_ready = 0;
	if (musb_ep_get_qh(qh->hw_ep, is_in) == qh) {
		urb = next_urb(qh);


		if (!urb->unlinked)
			urb->status = -ESHUTDOWN;


		musb_cleanup_urb(urb, qh);


		while (!list_empty(&hep->urb_list)) {
			urb = next_urb(qh);
			urb->status = -ESHUTDOWN;
			musb_advance_schedule(musb, urb, qh->hw_ep, is_in);
		}
	} else {


		while (!list_empty(&hep->urb_list))
			musb_giveback(musb, next_urb(qh), -ESHUTDOWN);

		hep->hcpriv = NULL;
		list_del(&qh->ring);
		kfree(qh);
	}
exit:
	spin_unlock_irqrestore(&musb->lock, flags);
}
