ibm_sector_header (FDI *fdi, uae_u8 *data, uae_u8 *crc, int secnum, int pre)
{
	uae_u8 secbuf[5];
	uae_u8 crcbuf[2];
	uae_u16 crcv;
	int i;

	if (pre)
		bytes_mfm_add (fdi, 0, 12);
	word_add (fdi, 0x4489);
	word_add (fdi, 0x4489);
	word_add (fdi, 0x4489);
	secbuf[0] = 0xfe;
	if (secnum >= 0) {
		secbuf[1] = (uae_u8)(fdi->current_track/2);
		secbuf[2] = (uae_u8)(fdi->current_track%2);
		secbuf[3] = (uae_u8)secnum;
		secbuf[4] = 2;
	} else {
		memcpy (secbuf + 1, data, 4);
	}
	ibm_crc (secbuf[0], 1);
	ibm_crc (secbuf[1], 0);
	ibm_crc (secbuf[2], 0);
	ibm_crc (secbuf[3], 0);
	crcv = ibm_crc (secbuf[4], 0);
	if (crc) {
		memcpy (crcbuf, crc, 2);
	} else {
		crcbuf[0] = (uae_u8)(crcv >> 8);
		crcbuf[1] = (uae_u8)crcv;
	}

	for (i = 0;i < 5; i++)
		byte_mfm_add (fdi, secbuf[i]);

	byte_mfm_add (fdi, crcbuf[0]);
	byte_mfm_add (fdi, crcbuf[1]);
}
