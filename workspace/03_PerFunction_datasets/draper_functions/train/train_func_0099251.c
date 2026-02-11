adsi_display(unsigned char *buf, int page, int line, int just, int wrap,
		 char *col1, char *col2)
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

	buf[bytes++] = ADSI_LOAD_VIRTUAL_DISP;


	bytes++;


	buf[bytes++] = ((page & 0x1) << 7) | ((wrap & 0x1) << 6) | (line & 0x3f);


	buf[bytes++] = (just & 0x3) << 5;


	buf[bytes++] = 0xff;


	bytes+= ccopy(buf + bytes, (unsigned char *)col1, 20);


	buf[bytes++] = 0xff;


	bytes += ccopy(buf + bytes, (unsigned char *)col2, 20);


	buf[1] = bytes - 2;

	return bytes;

}
