fputs_backtick(const char *s, FILE *stream)
{
	unsigned i;
	unsigned long tab_pos;
	unsigned long tab_len;

	for (; *s != '\0'; ++s)
		switch (*s) {
		case '\t':
			tab_pos = next_tab(line_col);
			tab_len = tab_pos - line_col;
			for (i = 0; i < tab_len; ++i)
				fputc(' ', stream);
			line_col = tab_pos;
			break;
		case '\\':
			fputs("\\\\", stream);
			++line_col;
			break;
		case '\n':
		case '\r':
		case '\f':
			fputc(*s, stream);
			line_col = 0;
			break;
		default:
			fputc(*s, stream);
			++line_col;
		}
}
