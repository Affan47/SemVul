prune_directory(struct dir_struct *dir, const char **pathspec, int prefix)
{
	char *seen;
	int i, specs;
	struct dir_entry **src, **dst;

	for (specs = 0; pathspec[specs];  specs++)
		;
	seen = xcalloc(specs, 1);

	src = dst = dir->entries;
	i = dir->nr;
	while (--i >= 0) {
		struct dir_entry *entry = *src++;
		if (match_pathspec(pathspec, entry->name, entry->len,
				   prefix, seen))
			*dst++ = entry;
	}
	dir->nr = dst - dir->entries;

	for (i = 0; i < specs; i++) {
		if (!seen[i] && !file_exists(pathspec[i]))
			die("pathspec '%s' did not match any files",
					pathspec[i]);
	}
        free(seen);
}
