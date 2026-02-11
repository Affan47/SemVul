picolcd_20x2_write(usb_dev_handle *lcd, const int row, const int col, const unsigned char *data)
{
	unsigned char packet[64] = { 0x98 };
	int len = strlen((char *) data);


	if (len > 20)
		len = 20;


	packet[1] = row;
	packet[2] = col;
	packet[3] = len;

	memcpy(packet + 4, data, len);

	picolcd_send(lcd, packet, 4 + len);
}
