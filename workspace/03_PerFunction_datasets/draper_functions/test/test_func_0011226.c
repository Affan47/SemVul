riello_calc_CRC(BYTE type, BYTE *buff, WORD size, BYTE checksum)
{
	int i;
	WORD pom, CRC_Word;

	CRC_Word = 0;
	switch (type) {
		case DEV_RIELLOSENTRY:
			CRC_Word = 0;
			if (size == 101) {
				for (i=0; i<100; i++)
					CRC_Word += buff[i];
			}
			else {
				for (i=0; i<size; i++)
					CRC_Word += buff[i];
			}
			break;
		case DEV_RIELLOGPSER:
			if (checksum) {
				buff++;
				size--;
				CRC_Word = 0x554D;
				while(size--) {
					pom = (CRC_Word ^ *buff) & 0xff;
					pom = (pom ^ (pom << 4)) & 0xff;
					pom = (pom << 8) ^ (pom << 3) ^ (pom >> 4);
					CRC_Word = (CRC_Word >> 8) ^ pom;
					buff++;
				}
			}
			else {
				CRC_Word = 0;
				for (i=1; i<size; i++)
					CRC_Word += buff[i];
			}
			break;
	}
	return(CRC_Word);
}
