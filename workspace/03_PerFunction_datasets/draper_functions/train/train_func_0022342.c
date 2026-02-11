is_subdir(const char *name, int namelen,
		const char *match, int matchlen, int max_depth)
{
	if (matchlen > namelen || strncmp(name, match, matchlen))
		return 0;

	if (name[matchlen] == '\0')
		return 1;

	if (!matchlen || match[matchlen-1] == '/' || name[matchlen] == '/')
		return accept_subdir(name + matchlen + 1, max_depth);

	return 0;
}
