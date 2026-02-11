safe_output(FILE *stream, unsigned char *str)
{
	unsigned char *p;

	for (p = str; *p != '\0'; ++p) {


		if (*p < 0x20 || *p >= 0x7f) {
			*p = '?';
		}
	}

	fprintf(stream, "%s", str);
}
