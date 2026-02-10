pcan_usb_get_serial(struct peak_usb_device *dev, u32 *serial_number)
{
	u8 args[PCAN_USB_CMD_ARGS_LEN];
	int err;

	err = pcan_usb_wait_rsp(dev, 6, 1, args);
	if (err) {
		netdev_err(dev->netdev, "getting serial failure: %d\n", err);
	} else if (serial_number) {
		__le32 tmp32;

		memcpy(&tmp32, args, 4);
		*serial_number = le32_to_cpu(tmp32);
	}

	return err;
}
