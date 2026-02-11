fotg210_handle_intr_unlinks(struct fotg210_hcd *fotg210)
{
	bool stopped = (fotg210->rh_state < FOTG210_RH_RUNNING);


	fotg210->intr_unlinking = true;
	while (fotg210->intr_unlink) {
		struct fotg210_qh *qh = fotg210->intr_unlink;

		if (!stopped && qh->unlink_cycle == fotg210->intr_unlink_cycle)
			break;
		fotg210->intr_unlink = qh->unlink_next;
		qh->unlink_next = NULL;
		end_unlink_intr(fotg210, qh);
	}


	if (fotg210->intr_unlink) {
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_UNLINK_INTR,
				true);
		++fotg210->intr_unlink_cycle;
	}
	fotg210->intr_unlinking = false;
}
