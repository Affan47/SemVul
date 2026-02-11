device_id(int fd, unsigned char *buffer, int size)
{
	libusb_device_handle *hd;
	int config,interface,alt;
	int len=0, rlen, maxSize;

	hd = fd_table[fd].hd;
	config = fd_table[fd].config;
	interface = fd_table[fd].interface;
	alt = fd_table[fd].alt_setting;

	if (hd == NULL)
	{
		BUG("invalid device_id state\n");
		goto bugout;
	}

	maxSize = (size > 1024) ? 1024 : size;

	rlen = libusb_control_transfer(hd,
			LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE,
			LIBUSB_REQUEST_GET_STATUS,
			config,
			interface,
			buffer, maxSize, LIBUSB_CONTROL_REQ_TIMEOUT);

	if (rlen < 0)
	{
		BUG("invalid deviceid ret=%d: %m\n", rlen);
		goto bugout;
	}

	len = ntohs(*(short *)buffer);
	if (len > (size-1))
		len = size-1;
	if (len > 2)
		len -= 2;
	memcpy(buffer, buffer+2, len);
	buffer[len]=0;
	DBG("read actual device_id successfully fd=%d len=%d\n", fd, len);

bugout:
	return len;
}
