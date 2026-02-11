append_string(char *buf, const char *s, size_t bufsize)
{
	int pos = strlen(buf), spos = 0, error = -1;

	if (pos >= bufsize - 4)
		return -1;

	buf[pos++] = '\"';

	while(pos < bufsize - 3) {
		if (!s[spos]) {
			error = 0;
			break;
		}
		if (s[spos] == '\"')
			buf[pos++] = '\"';
		buf[pos++] = s[spos];
		spos++;
	}

	buf[pos++] = '\"';
	buf[pos++] = ',';
	buf[pos++] = '\0';

	return error;
}
