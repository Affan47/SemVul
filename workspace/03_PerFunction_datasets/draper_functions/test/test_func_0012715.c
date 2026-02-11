ipheth_get_macaddr(struct ipheth_device *dev)
{
	struct usb_device *udev = dev->udev;
	struct net_device *net = dev->net;
	int retval;

	retval = usb_control_msg(udev,
				 usb_rcvctrlpipe(udev, IPHETH_CTRL_ENDP),
				 IPHETH_CMD_GET_MACADDR,
				 0xc0,
				 0x00,
				 0x02,
				 dev->ctrl_buf,
				 IPHETH_CTRL_BUF_SIZE,
				 IPHETH_CTRL_TIMEOUT);
	if (retval < 0) {
		dev_err(&dev->intf->dev, "%s: usb_control_msg: %d\n",
			__func__, retval);
	} else if (retval < ETH_ALEN) {
		dev_err(&dev->intf->dev,
			"%s: usb_control_msg: short packet: %d bytes\n",
			__func__, retval);
		retval = -EINVAL;
	} else {
		memcpy(net->dev_addr, dev->ctrl_buf, ETH_ALEN);
		retval = 0;
	}

	return retval;
}
