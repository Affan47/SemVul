pretty_print_string(void)
{
	u8 len;
	u8 *strptr;
	int indx;
	bool in_parens = FALSE;

	strptr = get_string(&len);

	printf("( len=%s%x", len >= 10 ? "0x" : "", len);
	if (len >= 10)
		printf(" [%d bytes]", len);
	printf(" )\n");
	if (show_linenumbers)
		printf("        ");
	decode_indent();
	printf("\" ");

	for (indx = 0; indx < len; indx++) {
		u8 c = *strptr++;
		if (isprint(c)) {
			if (in_parens) {
				printf(" )");
				in_parens = FALSE;
			}
			printf("%c", c);

			if (c == '"')
				printf("%c", c);
		} else {
			if (!in_parens) {
				printf("\"(");
				in_parens = TRUE;
			}
			printf(" %02x", c);
		}
	}
	if (in_parens)
		printf(" )");
	printf("\"");
}
