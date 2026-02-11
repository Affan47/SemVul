kobil_ioctl(struct tty_struct *tty,
					unsigned int cmd, unsigned long arg)
{
	struct usb_serial_port *port = tty->driver_data;
	struct kobil_private *priv = usb_get_serial_port_data(port);
	int result;

	if (priv->device_type == KOBIL_USBTWIN_PRODUCT_ID ||
			priv->device_type == KOBIL_KAAN_SIM_PRODUCT_ID)

		return -ENOIOCTLCMD;

	switch (cmd) {
	case TCFLSH:
		result = usb_control_msg(port->serial->dev,
			  usb_sndctrlpipe(port->serial->dev, 0),
			  SUSBCRequest_Misc,
			  USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_DIR_OUT,
			  SUSBCR_MSC_ResetAllQueues,
			  0,
			  NULL,
			  0,
			  KOBIL_TIMEOUT
			);

		dev_dbg(&port->dev,
			"%s - Send reset_all_queues (FLUSH) URB returns: %i\n",
			__func__, result);
		return (result < 0) ? -EIO: 0;
	default:
		return -ENOIOCTLCMD;
	}
}
