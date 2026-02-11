math_fill(char *str, long width)
{
	if (width > 0) {
		width -= (long)strlen(str);
		while (width-- > 0)
			PUTCHAR(' ');
		PUTSTR(str);
	} else {
		width += (long)strlen(str);
		PUTSTR(str);
		while (width++ < 0)
			PUTCHAR(' ');
	}
}
