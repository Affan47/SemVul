emit_line(const char *set, const char *reset, const char *line, int len)
{
	if (len > 0 && line[len-1] == '\n')
		len--;
	fputs(set, stdout);
	fwrite(line, len, 1, stdout);
	puts(reset);
}
