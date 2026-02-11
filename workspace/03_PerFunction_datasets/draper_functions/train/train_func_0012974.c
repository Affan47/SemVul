dl_send_data(void * handle, const uint8_t * data, int size)
{
	unsigned int crc = 0, i;
	iface_putchar(handle, API_HEADER);
	phy_putchar(handle, (size >> 8) & 0xFF);
	phy_putchar(handle, size & 0xFF);
	for (i = 0; i < size; i++) {
		uint8_t ch = data[i];
		crc += ch;
		phy_putchar(handle, ch);
	}

	phy_putchar(handle, (0xFF - crc) & 0xFF);
	return 0;
}
