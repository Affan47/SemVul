print_gfs2(const char *fmt, ...)
{
	va_list args;
	char string[PATH_MAX];

	memset(string, 0, sizeof(string));
	va_start(args, fmt);
	vsprintf(string, fmt, args);
	if (termlines)
		printw("%s", string);
	else
		printf("%s", string);
	va_end(args);
}
