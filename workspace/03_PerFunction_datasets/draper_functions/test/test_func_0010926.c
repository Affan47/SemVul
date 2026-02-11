az6027_identify_state(struct usb_device *udev,
				 struct dvb_usb_device_properties *props,
				 struct dvb_usb_device_description **desc,
				 int *cold)
{
	u8 *b;
	s16 ret;

	b = kmalloc(16, GFP_KERNEL);
	if (!b)
		return -ENOMEM;

	ret = usb_control_msg(udev,
				  usb_rcvctrlpipe(udev, 0),
				  0xb7,
				  USB_TYPE_VENDOR | USB_DIR_IN,
				  6,
				  0,
				  b,
				  6,
				  USB_CTRL_GET_TIMEOUT);

	*cold = ret <= 0;
	kfree(b);
	deb_info("cold: %d\n", *cold);
	return 0;
}
