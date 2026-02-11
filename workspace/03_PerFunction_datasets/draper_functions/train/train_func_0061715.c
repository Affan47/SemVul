ndmbstf_getline (FILE *fp, char *buf, unsigned max_buf)
{
	char *		p = buf;
	char *		p_end = buf + max_buf - 2;
	int		c;

	while ((c = getc(fp)) != EOF) {
#ifdef SELF_TEST
		n_getc++;
#endif
		if (c == '\n')
			break;
		if (p < p_end)
			*p++ = c;
	}
	*p = 0;

	if (c == EOF) {
		if (p > buf)
			return -2;
		return EOF;
	}

#ifdef SELF_TEST
	n_line++;
#endif
	return p - buf;
}
