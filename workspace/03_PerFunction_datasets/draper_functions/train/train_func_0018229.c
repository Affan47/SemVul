out_line_count (str)
     const char *str;
{
	register int i;

	for (i = 0; str[i]; ++i)
		if (str[i] == '\n')
			++out_linenum;
}
