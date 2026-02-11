btusb_qca_send_vendor_req(struct hci_dev *hdev, u8 request,
				     void *data, u16 size)
{
	struct btusb_data *btdata = hci_get_drvdata(hdev);
	struct usb_device *udev = btdata->udev;
	int pipe, err;
	u8 *buf;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;


	pipe = usb_rcvctrlpipe(udev, 0);
	err = usb_control_msg(udev, pipe, request, USB_TYPE_VENDOR | USB_DIR_IN,
			      0, 0, buf, size, USB_CTRL_SET_TIMEOUT);
	if (err < 0) {
		BT_ERR("%s: Failed to access otp area (%d)", hdev->name, err);
		goto done;
	}

	memcpy(data, buf, size);

done:
	kfree(buf);

	return err;
}
