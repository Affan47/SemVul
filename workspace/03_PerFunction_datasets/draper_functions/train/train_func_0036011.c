print_line_info(pCPP_ struct lexer_state *ls, unsigned long flags)
{
	char *fn = current_long_filename ?
		current_long_filename : current_filename;
	char *b, *d;

	b = getmem(50 + strlen(fn));
	if (flags & GCC_LINE_NUM) {
		sprintf(b, "# %ld \"%s\"\n", ls->line, fn);
	} else {
		sprintf(b, "#line %ld \"%s\"\n", ls->line, fn);
	}
	for (d = b; *d; d ++) put_char(aCPP_ ls, (unsigned char)(*d));
	freemem(b);
}
