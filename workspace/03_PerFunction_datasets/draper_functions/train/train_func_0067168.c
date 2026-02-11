mk_remount_opts(const char *old, const char *instead)
{
	char *new;
	size_t sz;

	if (old == NULL && instead == NULL)
		return NULL;
	if (!old)
		return xstrdup(instead);


	sz = strlen(old) + (instead ? strlen(instead) : 0) + 2;
	new = xmalloc(sz);
	if (instead && *instead)
		strncpy(new, instead, sz);
	else
		*new = '\0';

	cpy_option("loop=", new, old);

	return new;
}
