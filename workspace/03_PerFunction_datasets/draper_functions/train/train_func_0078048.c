mos7720_startup(struct usb_serial *serial)
{
	struct usb_device *dev;
	char data;
	u16 product;
	int ret_val;

	if (serial->num_bulk_in < 2 || serial->num_bulk_out < 2) {
		dev_err(&serial->interface->dev, "missing bulk endpoints\n");
		return -ENODEV;
	}

	product = le16_to_cpu(serial->dev->descriptor.idProduct);
	dev = serial->dev;


	if (product == MOSCHIP_DEVICE_ID_7715) {
		struct usb_serial_port *tmp = serial->port[0];
		serial->port[0] = serial->port[1];
		serial->port[1] = tmp;
		serial->port[0]->interrupt_in_urb = tmp->interrupt_in_urb;
		serial->port[0]->interrupt_in_buffer = tmp->interrupt_in_buffer;
		serial->port[0]->interrupt_in_endpointAddress =
			tmp->interrupt_in_endpointAddress;
		serial->port[1]->interrupt_in_urb = NULL;
		serial->port[1]->interrupt_in_buffer = NULL;

		if (serial->port[0]->interrupt_in_urb) {
			struct urb *urb = serial->port[0]->interrupt_in_urb;

			urb->complete = mos7715_interrupt_callback;
		}
	}


	usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			(__u8)0x03, 0x00, 0x01, 0x00, NULL, 0x00, 5000);

#ifdef CONFIG_USB_SERIAL_MOS7715_PARPORT
	if (product == MOSCHIP_DEVICE_ID_7715) {
		ret_val = mos7715_parport_init(serial);
		if (ret_val < 0)
			return ret_val;
	}
#endif

	ret_val = usb_submit_urb(serial->port[0]->interrupt_in_urb, GFP_KERNEL);
	if (ret_val) {
		dev_err(&dev->dev, "failed to submit interrupt urb: %d\n",
			ret_val);
	}


	read_mos_reg(serial, 0, MOS7720_LSR, &data);
	dev_dbg(&dev->dev, "LSR:%x\n", data);

	return 0;
}
