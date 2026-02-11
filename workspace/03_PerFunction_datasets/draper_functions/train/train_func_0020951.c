nfcmrvl_submit_bulk_urb(struct nfcmrvl_usb_drv_data *drv_data, gfp_t mem_flags)
{
	struct urb *urb;
	unsigned char *buf;
	unsigned int pipe;
	int err, size = NFCMRVL_NCI_MAX_EVENT_SIZE;

	if (!drv_data->bulk_rx_ep)
		return -ENODEV;

	urb = usb_alloc_urb(0, mem_flags);
	if (!urb)
		return -ENOMEM;

	buf = kmalloc(size, mem_flags);
	if (!buf) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	pipe = usb_rcvbulkpipe(drv_data->udev,
			       drv_data->bulk_rx_ep->bEndpointAddress);

	usb_fill_bulk_urb(urb, drv_data->udev, pipe, buf, size,
			  nfcmrvl_bulk_complete, drv_data);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_mark_last_busy(drv_data->udev);
	usb_anchor_urb(urb, &drv_data->bulk_anchor);

	err = usb_submit_urb(urb, mem_flags);
	if (err) {
		if (err != -EPERM && err != -ENODEV)
			nfc_err(&drv_data->udev->dev,
				"urb %p submission failed (%d)\n", urb, -err);
		usb_unanchor_urb(urb);
	}

	usb_free_urb(urb);

	return err;
}
