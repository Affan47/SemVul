git_attr_cache__is_cached(
	git_repository *repo,
	git_attr_file_source source,
	const char *filename)
{
	git_attr_cache *cache = git_repository_attr_cache(repo);
	git_strmap *files;
	khiter_t pos;
	git_attr_file_entry *entry;

	if (!cache || !(files = cache->files))
		return false;

	pos = git_strmap_lookup_index(files, filename);
	if (!git_strmap_valid_index(files, pos))
		return false;

	entry = git_strmap_value_at(files, pos);

	return entry && (entry->file[source] != NULL);
}
