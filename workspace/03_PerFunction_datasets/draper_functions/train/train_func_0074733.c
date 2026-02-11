listglob(List *list, char *pattern, char *quote, size_t slashcount) {
	List *result, **prevp;

	for (result = NULL, prevp = &result; list != NULL; list = list->next) {
		const char *dir;
		size_t dirlen;
		static char *prefix = NULL;
		static size_t prefixlen = 0;

		assert(list->term != NULL);
		assert(!isclosure(list->term));

		dir = getstr(list->term);
		dirlen = strlen(dir);
		if (dirlen + slashcount + 1 >= prefixlen) {
			prefixlen = dirlen + slashcount + 1;
			prefix = erealloc(prefix, prefixlen);
		}
		memcpy(prefix, dir, dirlen);
		memset(prefix + dirlen, '/', slashcount);
		prefix[dirlen + slashcount] = '\0';

		*prevp = dirmatch(prefix, dir, pattern, quote);
		while (*prevp != NULL)
			prevp = &(*prevp)->next;
	}
	return result;
}
