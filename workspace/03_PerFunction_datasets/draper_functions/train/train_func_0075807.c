ath9k_hif_usb_dealloc_tx_urbs(struct hif_device_usb *hif_dev)
{
	struct tx_buf *tx_buf = NULL, *tx_buf_tmp = NULL;
	unsigned long flags;

	list_for_each_entry_safe(tx_buf, tx_buf_tmp,
				 &hif_dev->tx.tx_buf, list) {
		usb_kill_urb(tx_buf->urb);
		list_del(&tx_buf->list);
		usb_free_urb(tx_buf->urb);
		kfree(tx_buf->buf);
		kfree(tx_buf);
	}

	spin_lock_irqsave(&hif_dev->tx.tx_lock, flags);
	hif_dev->tx.flags |= HIF_USB_TX_FLUSH;
	spin_unlock_irqrestore(&hif_dev->tx.tx_lock, flags);

	list_for_each_entry_safe(tx_buf, tx_buf_tmp,
				 &hif_dev->tx.tx_pending, list) {
		usb_kill_urb(tx_buf->urb);
		list_del(&tx_buf->list);
		usb_free_urb(tx_buf->urb);
		kfree(tx_buf->buf);
		kfree(tx_buf);
	}

	usb_kill_anchored_urbs(&hif_dev->mgmt_submitted);
}
