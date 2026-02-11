mxuport_calc_num_ports(struct usb_serial *serial)
{
	unsigned long features = (unsigned long)usb_get_serial_data(serial);

	if (features & MX_UPORT_2_PORT)
		return 2;
	if (features & MX_UPORT_4_PORT)
		return 4;
	if (features & MX_UPORT_8_PORT)
		return 8;
	if (features & MX_UPORT_16_PORT)
		return 16;

	return 0;
}
