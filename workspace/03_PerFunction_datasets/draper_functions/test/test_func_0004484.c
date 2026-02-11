ends_rfc2822_footer(struct strbuf *sb)
{
	int ch;
	int hit = 0;
	int i, j, k;
	int len = sb->len;
	int first = 1;
	const char *buf = sb->buf;

	for (i = len - 1; i > 0; i--) {
		if (hit && buf[i] == '\n')
			break;
		hit = (buf[i] == '\n');
	}

	while (i < len - 1 && buf[i] == '\n')
		i++;

	for (; i < len; i = k) {
		for (k = i; k < len && buf[k] != '\n'; k++)
			;
		k++;

		if ((buf[k] == ' ' || buf[k] == '\t') && !first)
			continue;

		first = 0;

		for (j = 0; i + j < len; j++) {
			ch = buf[i + j];
			if (ch == ':')
				break;
			if (isalnum(ch) ||
			    (ch == '-'))
				continue;
			return 0;
		}
	}
	return 1;
}
