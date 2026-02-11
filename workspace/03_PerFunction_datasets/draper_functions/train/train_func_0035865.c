cf_add_chksum_long(uint seed, ubyte *buffer, int size)
{
	uint crc;
	ubyte *p;

	p = buffer;
	crc = seed;

	while (size--)
		crc = (crc >> 8) ^ CRCTable[(crc ^ *p++) & 0xff];

	return crc;
}
