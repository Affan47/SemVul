sddr09_request_sense(struct us_data *us, unsigned char *sensebuf, int buflen) {
	unsigned char *command = us->iobuf;
	int result;

	memset(command, 0, 12);
	command[0] = 0x03;
	command[1] = LUNBITS;
	command[4] = buflen;

	result = sddr09_send_scsi_command(us, command, 12);
	if (result)
		return result;

	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
			sensebuf, buflen, NULL);
	return (result == USB_STOR_XFER_GOOD ? 0 : -EIO);
}
