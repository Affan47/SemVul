symbol_startup(struct usb_serial *serial)
{
	if (!serial->num_interrupt_in) {
		dev_err(&serial->dev->dev, "no interrupt-in endpoint\n");
		return -ENODEV;
	}

	return 0;
}
