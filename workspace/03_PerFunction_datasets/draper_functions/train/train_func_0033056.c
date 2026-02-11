CRC_Block (byte *start, int count)
{
	unsigned short	crc;

	CRC_Init (&crc);
	while (count--)
		crc = (crc << 8) ^ crctable[(crc >> 8) ^ *start++];

	return crc;
}
