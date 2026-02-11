wa_urb_enqueue_run(struct work_struct *ws)
{
	struct wahc *wa = container_of(ws, struct wahc, xfer_enqueue_work);
	struct wa_xfer *xfer, *next;
	struct urb *urb;
	LIST_HEAD(tmp_list);


	spin_lock_irq(&wa->xfer_list_lock);
	list_cut_position(&tmp_list, &wa->xfer_delayed_list,
			wa->xfer_delayed_list.prev);
	spin_unlock_irq(&wa->xfer_list_lock);


	list_for_each_entry_safe(xfer, next, &tmp_list, list_node) {
		list_del_init(&xfer->list_node);

		urb = xfer->urb;
		if (wa_urb_enqueue_b(xfer) < 0)
			wa_xfer_giveback(xfer);
		usb_put_urb(urb);
	}
}
