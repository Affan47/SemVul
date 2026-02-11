mc_create_buffer (Magicolor_Scanner *s, unsigned char cmd_type, unsigned char cmd,
		      unsigned char **buf, unsigned char* arg1, size_t len1,
		      SANE_Status *status)
{
	unsigned char* b = NULL;
	size_t buf_len = 2+4+len1+4;
	NOT_USED (s);
	if (len1 <= 0)
		buf_len = 6;
	*buf = b = malloc (buf_len);
	memset (b, 0x00, buf_len);
	if (!b) {
		*status = SANE_STATUS_NO_MEM;
		return 0;
	}
	b[0] = cmd_type;
	b[1] = cmd;
	if (len1>0) {
		b[2] = len1 & 0xff;
		b[3] = (len1 >> 8) & 0xff;
		b[4] = (len1 >> 16) & 0xff;
		b[5] = (len1 >> 24) & 0xff;
		if (arg1)
			memcpy(b+6, arg1, len1);
	}

	*status = SANE_STATUS_GOOD;
	return buf_len;
}
