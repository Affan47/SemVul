sddr09_readX(struct us_data *us, int x, unsigned long fromaddress,
	     int nr_of_pages, int bulklen, unsigned char *buf,
	     int use_sg) {

	unsigned char *command = us->iobuf;
	int result;

	command[0] = 0xE8;
	command[1] = LUNBITS | x;
	command[2] = MSB_of(fromaddress>>16);
	command[3] = LSB_of(fromaddress>>16);
	command[4] = MSB_of(fromaddress & 0xFFFF);
	command[5] = LSB_of(fromaddress & 0xFFFF);
	command[6] = 0;
	command[7] = 0;
	command[8] = 0;
	command[9] = 0;
	command[10] = MSB_of(nr_of_pages);
	command[11] = LSB_of(nr_of_pages);

	result = sddr09_send_scsi_command(us, command, 12);

	if (result) {
		usb_stor_dbg(us, "Result for send_control in sddr09_read2%d %d\n",
			     x, result);
		return result;
	}

	result = usb_stor_bulk_transfer_sg(us, us->recv_bulk_pipe,
				       buf, bulklen, use_sg, NULL);

	if (result != USB_STOR_XFER_GOOD) {
		usb_stor_dbg(us, "Result for bulk_transfer in sddr09_read2%d %d\n",
			     x, result);
		return -EIO;
	}
	return 0;
}
