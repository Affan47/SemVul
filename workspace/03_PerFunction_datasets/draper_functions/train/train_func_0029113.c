pretty_print(unsigned char *data, size_t length) {
	size_t i;
	int c;

	for (i = 0; i < length; i++) {
		c = data[i];
		switch(c) {
		default:
			if (isprint(c))
				putchar(c);
			else
				printf("<%d>", c);
			break;
		case TAB: fputs("<TAB>", stdout); break;
		case LF: fputs("<LF>\n", stdout); break;
		case CR: fputs("<CR>", stdout); break;
		case STX: fputs("<STX>", stdout); break;
		case ETX: fputs("<ETX>\n", stdout); break;
		}
	}
	fflush(stdout);
}
