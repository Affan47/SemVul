lbl_decode_static (unsigned char *code, int bits, int codepage)
{
	static char buf[4][512];
	static unsigned int bufid = 0;
	int currid = (bufid ++) % 4;

	buf[currid][0] = '\0';
	switch (bits) {

		case 6: lbl_decode6(code, buf[currid], sizeof(buf[0])); break;
		case 8:
		case 9:
		case 10: lbl_decode8x(code, codepage, buf[currid], sizeof(buf[0])); break;
		default: return dump_unknown_bytes(code, 16);

	}
	return buf[currid];
}
