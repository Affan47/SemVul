getmsg(char *datafile_name, isc_buffer_t *pbuf)
{
	int			c;
	unsigned int		len;
	unsigned int		cnt;
	unsigned char		*p;
	FILE			*fp;
	unsigned int		buflen;

	fp = fopen(datafile_name, "r");
	if (fp == NULL) {
		t_info("No such file %s\n", datafile_name);
		return (0);
	}

	p = isc_buffer_used(pbuf);
	buflen = isc_buffer_availablelength(pbuf);
	cnt = 0;
	len = 0;
	while ((c = getc(fp)) != EOF) {
		unsigned int		val;
		if (	(c == ' ') || (c == '\t') ||
			(c == '\r') || (c == '\n'))
				continue;
		if (c == '#') {
			while ((c = getc(fp)) != '\n')
				;
			continue;
		}
		if (('0' <= c) && (c <= '9'))
			val = c - '0';
		else if (('a' <= c) && (c <= 'f'))
			val = c - 'a' + 10;
		else if (('A' <= c) && (c <= 'F'))
			val = c - 'A'+ 10;
		else {
			(void)fclose(fp);
			t_info("Bad format in datafile\n");
			return (0);
		}
		if ((len % 2) == 0) {
			*p = (val << 4);
		} else {
			*p += val;
			++p;
			++cnt;
			if (cnt >= buflen) {


				(void)fclose(fp);
				t_info("Buffer overflow error\n");
				return (0);
			}
		}
		++len;
	}
	(void)fclose(fp);

	if (len % 2) {
		t_info("Bad format in %s\n", datafile_name);
		return (0);
	}

	*p = '\0';
	isc_buffer_add(pbuf, cnt);
	return (cnt);
}
