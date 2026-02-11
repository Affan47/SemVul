riello_create_crc(BYTE type, BYTE *buff, WORD size, BYTE checksum)
{
	WORD CRC_Word;

	CRC_Word = riello_calc_CRC(type, buff, size, checksum);

	if (type == DEV_RIELLOGPSER) {
		buff[size++] = (BYTE) ((CRC_Word/4096)+0x30);
		buff[size++] = (BYTE) (((CRC_Word%4096)/256)+0x30);
		buff[size++] = (BYTE) ((((CRC_Word%4096)%256)/16)+0x30);
		buff[size] = (BYTE) ((((CRC_Word%4096)%256)%16)+0x30);
	}
}
