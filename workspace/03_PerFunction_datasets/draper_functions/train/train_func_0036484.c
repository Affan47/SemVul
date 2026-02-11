fmatch(direntry)
	struct DIRECT  *direntry;
{
	char           *string;

	string = direntry->d_name;

	if (!strcmp(pattern, "") || !strcmp(pattern, "*.*") || !strcmp(pattern, "*"))
		return (1);
	return (match(string, pattern));
}
