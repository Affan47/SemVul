redrat3_send_cmd(int cmd, struct redrat3_dev *rr3)
{
	struct usb_device *udev;
	u8 *data;
	int res;

	data = kzalloc(sizeof(u8), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	udev = rr3->udev;
	res = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), cmd,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
			      0x0000, 0x0000, data, sizeof(u8), HZ * 10);

	if (res < 0) {
		dev_err(rr3->dev, "%s: Error sending rr3 cmd res %d, data %d",
			__func__, res, *data);
		res = -EIO;
	} else
		res = data[0];

	kfree(data);

	return res;
}
