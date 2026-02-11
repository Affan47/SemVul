kalmia_send_init_packet(struct usbnet *dev, u8 *init_msg, u8 init_msg_len,
	u8 *buffer, u8 expected_len)
{
	int act_len;
	int status;

	netdev_dbg(dev->net, "Sending init packet");

	status = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 0x02),
		init_msg, init_msg_len, &act_len, KALMIA_USB_TIMEOUT);
	if (status != 0) {
		netdev_err(dev->net,
			"Error sending init packet. Status %i, length %i\n",
			status, act_len);
		return status;
	}
	else if (act_len != init_msg_len) {
		netdev_err(dev->net,
			"Did not send all of init packet. Bytes sent: %i",
			act_len);
	}
	else {
		netdev_dbg(dev->net, "Successfully sent init packet.");
	}

	status = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, 0x81),
		buffer, expected_len, &act_len, KALMIA_USB_TIMEOUT);

	if (status != 0)
		netdev_err(dev->net,
			"Error receiving init result. Status %i, length %i\n",
			status, act_len);
	else if (act_len != expected_len)
		netdev_err(dev->net, "Unexpected init result length: %i\n",
			act_len);

	return status;
}
