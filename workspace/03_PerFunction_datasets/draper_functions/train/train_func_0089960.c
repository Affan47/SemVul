identifier_is_tmp(const char *name)
{
	unsigned int i;

	if (name[0] != '_') return 0;
	if (name[1] != '_') return 0;
	for (i = 2; name[i]; i++) {
		if (! isdigit(name[i])) return 0;
	}
	return 1;
}
