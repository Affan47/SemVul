get_movetext_token(FILE * fp, char * buf, size_t bufsize)
{
	ASSERT(fp != NULL);
	char * p = buf;

	bool comment = false;

	while (!feof(fp) && p != buf + bufsize-1) {
		int c = fgetc(fp);
		if (c == EOF) {
			break;
		} else if (c == '\n' || c == '\r') {
			c = ' ';
		}

		if (comment) {
			*p++ = c;
			if (c == '}') {
				break;
			}
		} else {
			if (c == '{') {
				*p++ = c;
				comment = true;
			} else if (c == '.') {
				*p++ = c;
				break;
			} else if (c == ' ') {
				break;
			} else {
				*p++ = c;
			}
		}
	}
	*p = '\0';
	return buf;
}
