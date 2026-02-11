outstr(char *s)
{
	int len = (int)strlen(s);
	if (column + len > opt_width && len < opt_width) {
		outnl();
		column = 0;
	}
	for (; *s != '\0'; ++s) {
		if (*s == '\n')
			column = 0;
		else
			++column;
		putc(*s, output_file);
	}
}
