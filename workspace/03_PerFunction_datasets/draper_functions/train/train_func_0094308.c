endofname(const char *name)
	{
	char *p;

	p = (char *) name;
	if (! is_name(*p))
		return p;
	while (*++p) {
		if (! is_in_name(*p))
			break;
	}
	return p;
}
