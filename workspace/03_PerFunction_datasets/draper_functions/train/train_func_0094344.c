musb_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct musb		*musb = hcd_to_musb(hcd);
	struct musb_qh		*qh;
	unsigned long		flags;
	int			is_in  = usb_pipein(urb->pipe);
	int			ret;

	dev_dbg(musb->controller, "urb=%p, dev%d ep%d%s\n", urb,
			usb_pipedevice(urb->pipe),
			usb_pipeendpoint(urb->pipe),
			is_in ? "in" : "out");

	spin_lock_irqsave(&musb->lock, flags);
	ret = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (ret)
		goto done;

	qh = urb->hcpriv;
	if (!qh)
		goto done;


	if (!qh->is_ready
			|| urb->urb_list.prev != &qh->hep->urb_list
			|| musb_ep_get_qh(qh->hw_ep, is_in) != qh) {
		int	ready = qh->is_ready;

		qh->is_ready = 0;
		musb_giveback(musb, urb, 0);
		qh->is_ready = ready;


		if (ready && list_empty(&qh->hep->urb_list)) {
			qh->hep->hcpriv = NULL;
			list_del(&qh->ring);
			kfree(qh);
		}
	} else
		ret = musb_cleanup_urb(urb, qh);
done:
	spin_unlock_irqrestore(&musb->lock, flags);
	return ret;
}
