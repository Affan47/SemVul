crc32(void *data, size_t length)
{
	uint32_t crc, x;
	uint8_t i, *d;

	for(d = data, crc = 0xFFFFFFFF; length; length--)
	{
		x = (crc ^ *(d++)) & 0xFF;
		for(i = 8; i > 0; i--)
		{
			if(x & 1) x = (x >> 1) ^ 0xEDB88320;
			else x >>= 1;
		}
		crc = (crc >> 8) ^ x;
	}

	return(crc ^ 0xFFFFFFFF);
}
