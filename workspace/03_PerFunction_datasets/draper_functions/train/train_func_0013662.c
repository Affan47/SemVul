term__putc(EditLine *el, Int c)
{
	char buf[MB_LEN_MAX +1];
	ssize_t i;
	if (c == MB_FILL_CHAR)
		return 0;
	i = ct_encode_char(buf, MB_LEN_MAX, c);
	if (i <= 0)
		return (int)i;
	buf[i] = '\0';
	return fputs(buf, el->el_outfile);
}
