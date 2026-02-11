pcan_usb_send_cmd(struct peak_usb_device *dev, u8 f, u8 n, u8 *p)
{
	int err;
	int actual_length;


	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		return 0;

	dev->cmd_buf[PCAN_USB_CMD_FUNC] = f;
	dev->cmd_buf[PCAN_USB_CMD_NUM] = n;

	if (p)
		memcpy(dev->cmd_buf + PCAN_USB_CMD_ARGS,
			p, PCAN_USB_CMD_ARGS_LEN);

	err = usb_bulk_msg(dev->udev,
			usb_sndbulkpipe(dev->udev, PCAN_USB_EP_CMDOUT),
			dev->cmd_buf, PCAN_USB_CMD_LEN, &actual_length,
			PCAN_USB_COMMAND_TIMEOUT);
	if (err)
		netdev_err(dev->netdev,
			"sending cmd f=0x%x n=0x%x failure: %d\n",
			f, n, err);
	return err;
}
