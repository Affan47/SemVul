rfc1035_hostnamecmp(const char *p, const char *q)
{
	while (*p || *q)
	{
		if (*p == '.' || *q == '.' )
		{
			if ( (*p && *p != '.') || (*q && *q != '.'))
				return (1);
			while (*p == '.')	++p;
			while (*q == '.')	++q;
			continue;
		}
		if (!*p || !*q)	return (1);
		if ( tl(*p) != tl(*q))	return (1);
		++p;
		++q;
	}
	return (0);
}
