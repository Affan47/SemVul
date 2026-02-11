pzl_urb_dequeue(struct whc *whc, struct urb *urb, int status)
{
	struct whc_urb *wurb = urb->hcpriv;
	struct whc_qset *qset = wurb->qset;
	struct whc_std *std, *t;
	bool has_qtd = false;
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&whc->lock, flags);

	ret = usb_hcd_check_unlink_urb(&whc->wusbhc.usb_hcd, urb, status);
	if (ret < 0)
		goto out;

	list_for_each_entry_safe(std, t, &qset->stds, list_node) {
		if (std->urb == urb) {
			if (std->qtd)
				has_qtd = true;
			qset_free_std(whc, std);
		} else
			std->qtd = NULL;
	}

	if (has_qtd) {
		pzl_qset_remove(whc, qset);
		update_pzl_hw_view(whc);
		wurb->status = status;
		wurb->is_async = false;
		queue_work(whc->workqueue, &wurb->dequeue_work);
	} else
		qset_remove_urb(whc, qset, urb, status);
out:
	spin_unlock_irqrestore(&whc->lock, flags);

	return ret;
}
