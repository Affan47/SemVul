ppa_byte_out(unsigned short base, const char *buffer, int len)
{
	int i;

	for (i = len; i; i--) {
		w_dtr(base, *buffer++);
		w_ctr(base, 0xe);
		w_ctr(base, 0xc);
	}
	return 1;
}
