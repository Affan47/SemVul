oxu_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	struct ehci_qh *qh;
	unsigned long flags;

	spin_lock_irqsave(&oxu->lock, flags);
	switch (usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
	case PIPE_BULK:
	default:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		unlink_async(oxu, qh);
		break;

	case PIPE_INTERRUPT:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		switch (qh->qh_state) {
		case QH_STATE_LINKED:
			intr_deschedule(oxu, qh);

		case QH_STATE_IDLE:
			qh_completions(oxu, qh);
			break;
		default:
			oxu_dbg(oxu, "bogus qh %p state %d\n",
					qh, qh->qh_state);
			goto done;
		}


		if (!list_empty(&qh->qtd_list)
				&& HC_IS_RUNNING(hcd->state)) {
			int status;

			status = qh_schedule(oxu, qh);
			spin_unlock_irqrestore(&oxu->lock, flags);

			if (status != 0) {


				dev_err(hcd->self.controller,
					"can't reschedule qh %p, err %d\n", qh,
					status);
			}
			return status;
		}
		break;
	}
done:
	spin_unlock_irqrestore(&oxu->lock, flags);
	return 0;
}
