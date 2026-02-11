epox_endian_quirk(unsigned char *data, int size)
{


	unsigned char pattern[] = { 0x05, 0x07, 0x19, 0x00, 0x2a, 0x00, 0xff,
						0x15, 0x00, 0x26, 0x00, 0xff };
	unsigned int i;

	if (!data)
		return;

	for (i = 0; i < size - sizeof(pattern); i++) {
		if (!memcmp(data + i, pattern, sizeof(pattern))) {
			data[i + 5] = 0xff;
			data[i + 6] = 0x00;
			data[i + 10] = 0xff;
			data[i + 11] = 0x00;
		}
	}
}
