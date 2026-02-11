alloc_bulk_urb(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct urb *urb;
	unsigned int pipe;

	if (!data->bulk_tx_ep)
		return ERR_PTR(-ENODEV);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return ERR_PTR(-ENOMEM);

	pipe = usb_sndbulkpipe(data->udev, data->bulk_tx_ep->bEndpointAddress);

	usb_fill_bulk_urb(urb, data->udev, pipe,
			  skb->data, skb->len, btusb_tx_complete, skb);

	skb->dev = (void *)hdev;

	return urb;
}
