istgt_scsi_dump_cdb(uint8_t *cdb)
{
	int group;
	int cdblen = 0;
	int i;

	if (cdb == NULL)
		return;

	group = (cdb[0] >> 5) & 0x07;
	switch (group) {
	case 0x00:

		cdblen = 6;
		break;
	case 0x01:

		cdblen = 10;
		break;
	case 0x02:

		cdblen = 10;
		break;
	case 0x03:

		if (cdb[0] == 0x7f) {

			cdblen = 8 + (cdb[7] & 0xff);
		} else {

			cdblen = 6;
		}
		break;
	case 0x04:

		cdblen = 16;
		break;
	case 0x05:

		cdblen = 12;
		break;
	case 0x06:
	case 0x07:

		cdblen = 6;
		break;
	}

	printf("CDB=");
	for (i = 0; i < cdblen; i++) {
		printf("%2.2x ", cdb[i]);
	}
	printf("\n");
}
