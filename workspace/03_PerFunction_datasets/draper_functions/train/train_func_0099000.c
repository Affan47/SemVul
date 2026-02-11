ext2fs_crc16(crc16_t crc, const void *buffer, unsigned int len)
{
	const unsigned char *cp = buffer;

	while (len--)


		crc = (((crc >> 8) & 0xffU) ^
		       crc16_table[(crc ^ *cp++) & 0xffU]) & 0x0000ffffU;
	return crc;
}
