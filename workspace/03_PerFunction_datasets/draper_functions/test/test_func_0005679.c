bpa10x_submit_bulk_urb(struct hci_dev *hdev)
{
	struct bpa10x_data *data = hci_get_drvdata(hdev);
	struct urb *urb;
	unsigned char *buf;
	unsigned int pipe;
	int err, size = 64;

	BT_DBG("%s", hdev->name);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return -ENOMEM;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	pipe = usb_rcvbulkpipe(data->udev, 0x82);

	usb_fill_bulk_urb(urb, data->udev, pipe,
					buf, size, bpa10x_rx_complete, hdev);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &data->rx_anchor);

	err = usb_submit_urb(urb, GFP_KERNEL);
	if (err < 0) {
		BT_ERR("%s urb %p submission failed (%d)",
						hdev->name, urb, -err);
		usb_unanchor_urb(urb);
	}

	usb_free_urb(urb);

	return err;
}
