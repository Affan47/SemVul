c_getchar(int quote)
{
	int c;
	int space = 0;

	do {
		c = (unsigned char)c_buffer_getchar();
		if (quote || c_EOF) return c;

		if (c <= ' ') space = 1; else
		if (c == '/')
		switch ((c = c_buffer_getchar())) {
		case '/':
			do {
				c = c_buffer_getchar();
			} while (!c_EOF && c != '\n' && c != '\r');
			c = ' '; space = 1;
			break;

		case '*':
			do {
				if ((c = c_buffer_getchar()) == '*')
				if ((c = c_buffer_getchar()) == '/')
					break;
			} while (!c_EOF);
			c = ' '; space = 1;
			break;

		default:
			c_ungetchar(c);
			c = '/';
		}
	} while (c <= ' ');

	if (space) {
		c_ungetchar(c);
		c = ' ';
	}

	return c;
}
