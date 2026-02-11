update_some(const unsigned char *sha1, const char *base, int baselen,
		       const char *pathname, unsigned mode, int stage)
{
	int len;
	struct cache_entry *ce;

	if (S_ISGITLINK(mode))
		return 0;

	if (S_ISDIR(mode))
		return READ_TREE_RECURSIVE;

	len = baselen + strlen(pathname);
	ce = xcalloc(1, cache_entry_size(len));
	hashcpy(ce->sha1, sha1);
	memcpy(ce->name, base, baselen);
	memcpy(ce->name + baselen, pathname, len - baselen);
	ce->ce_flags = create_ce_flags(len, 0);
	ce->ce_mode = create_ce_mode(mode);
	add_cache_entry(ce, ADD_CACHE_OK_TO_ADD | ADD_CACHE_OK_TO_REPLACE);
	return 0;
}
