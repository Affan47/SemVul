irc_tolower_int(char *buf, int casemapping)
{
	char *p = buf;
	int upper_bound;


	switch (casemapping)
	{
		case IRC_CASEMAPPING_ASCII:		upper_bound = 'Z'; break;
		case IRC_CASEMAPPING_RFC1459_STRICT:	upper_bound = ']'; break;
		case IRC_CASEMAPPING_RFC1459:		upper_bound = '^'; break;
		default: debug_error ("bad value in call to irc_toupper_int: %d\n", casemapping); return 0;
	}
	while (*p)
	{

		if (*p >= 'A' && *p <= upper_bound)
			*p += 32;
		p++;
	}
	return buf;
}
