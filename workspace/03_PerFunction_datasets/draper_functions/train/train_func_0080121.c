usbtv_stop(struct usbtv *usbtv)
{
	int i;
	unsigned long flags;


	for (i = 0; i < USBTV_ISOC_TRANSFERS; i++) {
		struct urb *ip = usbtv->isoc_urbs[i];

		if (ip == NULL)
			continue;
		usb_kill_urb(ip);
		kfree(ip->transfer_buffer);
		usb_free_urb(ip);
		usbtv->isoc_urbs[i] = NULL;
	}


	spin_lock_irqsave(&usbtv->buflock, flags);
	while (!list_empty(&usbtv->bufs)) {
		struct usbtv_buf *buf = list_first_entry(&usbtv->bufs,
						struct usbtv_buf, list);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		list_del(&buf->list);
	}
	spin_unlock_irqrestore(&usbtv->buflock, flags);
}
