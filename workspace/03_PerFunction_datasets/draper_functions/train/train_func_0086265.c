usbat_read_block(struct us_data *us,
			    void* buf,
			    unsigned short len,
			    int use_sg)
{
	int result;
	unsigned char *command = us->iobuf;

	if (!len)
		return USB_STOR_TRANSPORT_GOOD;

	command[0] = 0xC0;
	command[1] = USBAT_ATA | USBAT_CMD_READ_BLOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;
	command[6] = LSB_of(len);
	command[7] = MSB_of(len);

	result = usbat_execute_command(us, command, 8);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	result = usbat_bulk_read(us, buf, len, use_sg);
	return (result == USB_STOR_XFER_GOOD ?
			USB_STOR_TRANSPORT_GOOD : USB_STOR_TRANSPORT_ERROR);
}
