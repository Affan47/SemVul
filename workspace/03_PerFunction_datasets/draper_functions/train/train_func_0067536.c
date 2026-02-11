imm_byte_in(unsigned short base, char *buffer, int len)
{
	int i;


	w_ctr(base, 0x4);
	for (i = len; i; i--) {
		w_ctr(base, 0x26);
		*buffer++ = r_dtr(base);
		w_ctr(base, 0x25);
	}
	return 1;
}
