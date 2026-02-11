as_hill_init(char *name, int len)
{
	struct as_hill * hill = XALLOC(as_hill);

	hill->name = strdup(name);
	hill->length = len;

	if (len < 0)
		hill->length *= -1;

	return hill;
}
