attach (char *dest, const char *dirname, const char *name)
{
	const char *dirnamep = dirname;


	if (dirname[0] != '.' || dirname[1] != 0)
	{
		while (*dirnamep) *dest++ = *dirnamep++;

		if (dirnamep > dirname && dirnamep[-1] != '/') *dest++ = '/';
	}
	while (*name) *dest++ = *name++;
	*dest = 0;
}
