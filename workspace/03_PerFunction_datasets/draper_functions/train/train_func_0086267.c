alloc_diag_urb(struct hci_dev *hdev, bool enable)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct sk_buff *skb;
	struct urb *urb;
	unsigned int pipe;

	if (!data->diag_tx_ep)
		return ERR_PTR(-ENODEV);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return ERR_PTR(-ENOMEM);

	skb = bt_skb_alloc(2, GFP_KERNEL);
	if (!skb) {
		usb_free_urb(urb);
		return ERR_PTR(-ENOMEM);
	}

	*skb_put(skb, 1) = 0xf0;
	*skb_put(skb, 1) = enable;

	pipe = usb_sndbulkpipe(data->udev, data->diag_tx_ep->bEndpointAddress);

	usb_fill_bulk_urb(urb, data->udev, pipe,
			  skb->data, skb->len, btusb_tx_complete, skb);

	skb->dev = (void *)hdev;

	return urb;
}
