pcan_usb_set_ext_vcc(struct peak_usb_device *dev, u8 onoff)
{
	u8 args[PCAN_USB_CMD_ARGS_LEN] = {
		[0] = !!onoff,
	};

	return pcan_usb_send_cmd(dev, 10, 2, args);
}
