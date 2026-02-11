maildir_parse_flags( const char *base )
{
	const char *s;
	unsigned i;
	unsigned char flags;

	flags = 0;
	if ((s = strstr( base, ":2," )))
		for (s += 3, i = 0; i < as(Flags); i++)
			if (strchr( s, Flags[i] ))
				flags |= (1 << i);
	return flags;
}
