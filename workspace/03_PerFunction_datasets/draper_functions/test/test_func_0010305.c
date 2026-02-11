adsi_set_line(unsigned char *buf, int page, int line)
{
	int bytes = 0;


	if (page) {
		if (line > 4) return -1;
	} else {
		if (line > 33) return -1;
	}

	if (line < 1) {
		return -1;
	}

	buf[bytes++] = ADSI_LINE_CONTROL;


	bytes++;


	buf[bytes++] = ((page & 0x1) << 7) | (line & 0x3f);

	buf[1] = bytes - 2;
	return bytes;
}
