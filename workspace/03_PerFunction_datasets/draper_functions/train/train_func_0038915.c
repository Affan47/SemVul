ipheth_carrier_set(struct ipheth_device *dev)
{
	struct usb_device *udev = dev->udev;
	int retval;

	retval = usb_control_msg(udev,
			usb_rcvctrlpipe(udev, IPHETH_CTRL_ENDP),
			IPHETH_CMD_CARRIER_CHECK,
			0xc0,
			0x00,
			0x02,
			dev->ctrl_buf, IPHETH_CTRL_BUF_SIZE,
			IPHETH_CTRL_TIMEOUT);
	if (retval < 0) {
		dev_err(&dev->intf->dev, "%s: usb_control_msg: %d\n",
			__func__, retval);
		return retval;
	}

	if (dev->ctrl_buf[0] == IPHETH_CARRIER_ON)
		netif_carrier_on(dev->net);
	else
		netif_carrier_off(dev->net);

	return 0;
}
