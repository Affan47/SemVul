decode_start(void)
{
	u8 fcformat;
	u16 fcchecksum, checksum = 0;

	output_token();
	printf("  ( %d-bit offsets)\n", offs16 ? 16 : 8);

	token_streampos = get_streampos();
	decode_lines();
	fcformat = get_num8();
	printf("  format:    0x%02x\n", fcformat);


	token_streampos = get_streampos();
	decode_lines();
	fcchecksum = get_num16();
	checksum = calc_checksum();

	if (fcchecksum == checksum) {
		printf("  checksum:  0x%04x (Ok)\n", fcchecksum);
	} else {
		printf("  checksum should be:  0x%04x, but is 0x%04x\n",
		       checksum, fcchecksum);
	}

	token_streampos = get_streampos();
	decode_lines();
	fclen = get_num32();
	printf("  len:       0x%04x ( %d bytes)\n", fclen, fclen);
}
