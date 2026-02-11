ohci_endpoint_disable (struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	struct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	unsigned long		flags;
	struct ed		*ed = ep->hcpriv;
	unsigned		limit = 1000;


	if (!ed)
		return;

rescan:
	spin_lock_irqsave (&ohci->lock, flags);

	if (ohci->rh_state != OHCI_RH_RUNNING) {
sanitize:
		ed->state = ED_IDLE;
		ohci_work(ohci);
	}

	switch (ed->state) {
	case ED_UNLINK:

		if (limit-- == 0) {
			ohci_warn(ohci, "ED unlink timeout\n");
			goto sanitize;
		}
		spin_unlock_irqrestore (&ohci->lock, flags);
		schedule_timeout_uninterruptible(1);
		goto rescan;
	case ED_IDLE:
		if (list_empty (&ed->td_list)) {
			td_free (ohci, ed->dummy);
			ed_free (ohci, ed);
			break;
		}

	default:


		ohci_err (ohci, "leak ed %p (#%02x) state %d%s\n",
			ed, ep->desc.bEndpointAddress, ed->state,
			list_empty (&ed->td_list) ? "" : " (has tds)");
		td_free (ohci, ed->dummy);
		break;
	}
	ep->hcpriv = NULL;
	spin_unlock_irqrestore (&ohci->lock, flags);
}
