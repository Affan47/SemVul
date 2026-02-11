conf_get_line (FILE *stream, char *buf, u_int32_t len)
{
	int c;

	while (len-- > 1) {
		c = fgetc (stream);
		if (c == '\n') {
			*buf = 0;
			return (1);
		}
		else if (c == EOF)
			break;

		*buf++ = c;
	}

	*buf = 0;
	return (0);
}
