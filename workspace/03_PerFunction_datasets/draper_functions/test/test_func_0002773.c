usblp_submit_read(struct usblp *usblp)
{
	struct urb *urb;
	unsigned long flags;
	int rc;

	rc = -ENOMEM;
	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (urb == NULL)
		goto raise_urb;

	usb_fill_bulk_urb(urb, usblp->dev,
		usb_rcvbulkpipe(usblp->dev,
		  usblp->protocol[usblp->current_protocol].epread->bEndpointAddress),
		usblp->readbuf, USBLP_BUF_SIZE_IN,
		usblp_bulk_read, usblp);
	usb_anchor_urb(urb, &usblp->urbs);

	spin_lock_irqsave(&usblp->lock, flags);
	usblp->readcount = 0;
	usblp->rcomplete = 0;
	spin_unlock_irqrestore(&usblp->lock, flags);
	if ((rc = usb_submit_urb(urb, GFP_KERNEL)) < 0) {
		dev_dbg(&usblp->intf->dev, "error submitting urb (%d)\n", rc);
		spin_lock_irqsave(&usblp->lock, flags);
		usblp->rstatus = rc;
		usblp->rcomplete = 1;
		spin_unlock_irqrestore(&usblp->lock, flags);
		goto raise_submit;
	}

	return 0;

raise_submit:
	usb_unanchor_urb(urb);
	usb_free_urb(urb);
raise_urb:
	return rc;
}
