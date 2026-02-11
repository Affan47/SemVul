analog_my_getsigstr(struct ast_channel *chan, char *str, const char *term, int ms)
{
	char c;

	*str = 0;
	for (;;) {

		c = ast_waitfordigit(chan, ms);

		if (c < 1) {
			return c;
		}
		*str++ = c;
		*str = 0;
		if (strchr(term, c)) {
			return 1;
		}
	}
}
