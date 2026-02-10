yywrap(void)
{
	if (found_defaults) {
		if (freopen(PREFIX, "r", stdin) == NULL)
			err(2, "%s", PREFIX);
		yyfile = PREFIX;
		yyline = 0;
		found_defaults = 0;
		return 0;
	}
	return 1;
}
