git_iterator_cmp(git_iterator *iter, const char *path_prefix)
{
	const git_index_entry *entry;


	if (git_iterator_current(&entry, iter) < 0 || entry == NULL)
		return 1;


	if (!path_prefix)
		return -1;

	return iter->prefixcomp(entry->path, path_prefix);
}
