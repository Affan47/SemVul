cp_usb_async_read(struct cp_usb_async *cp, uint8_t *valuep)
{
	int	p;
	int	ret;

	if (cp->p == MAX_OUTSTANDING)
		cp_usb_async_sync(cp);
	p = cp->p;
	if (!cp->packet[p].transfer)
		cp->packet[p].transfer = libusb_alloc_transfer(0);
	cp->packet[p].valuep = valuep;
	cp->packet[p].direction = packet_read;
	libusb_fill_control_setup(cp->packet[p].data,
				  0xc0,
				  0xff,
				  0x00c2,
				  0,
				  1);

	libusb_fill_control_transfer(cp->packet[p].transfer,
				     cp->handle,
				     cp->packet[p].data,
				     cp_usb_async_transfer_callback,
				     cp,
				     CP_TIMEOUT);
	ccdbg_debug(CC_DEBUG_USB_ASYNC, "Read packet %d\n", p);
	ret = libusb_submit_transfer(cp->packet[p].transfer);
	if (ret)
		fprintf(stderr, "libusb_submit_transfer failed %d\n", ret);
	cp->p++;
}
