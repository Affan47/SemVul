unescape(char arg[])
{
	char *p = arg;
	char escaped = '1';
	while ((p = strchr(p, '\\')) != NULL) {

		switch (p[1]) {
		case '0':

			fprintf(stderr, "bsqlodbc, line %d: NULL terminators ('\\0') not yet supported.\n", __LINE__);
			escaped = '\0';
			break;
		case 't':
			escaped = '\t';
			break;
		case 'r':
			escaped = '\r';
			break;
		case 'n':
			escaped = '\n';
			break;
		case '\\':
			escaped = '\\';
			break;
		default:
			break;
		}


		if (!isdigit((unsigned char) escaped)) {
			*p++ = escaped;
			memmove(p, p+1, 1 + strlen(p+1));
			escaped = '1';
		}
	}
}
