git_attr_cache__internal_file(
	git_repository *repo,
	const char *filename,
	git_attr_file **file)
{
	int error = 0;
	git_attr_cache *cache = git_repository_attr_cache(repo);
	khiter_t cache_pos = git_strmap_lookup_index(cache->files, filename);

	if (git_strmap_valid_index(cache->files, cache_pos)) {
		*file = git_strmap_value_at(cache->files, cache_pos);
		return 0;
	}

	if (git_attr_file__new(file, 0, filename, &cache->pool) < 0)
		return -1;

	git_strmap_insert(cache->files, (*file)->key + 2, *file, error);
	if (error > 0)
		error = 0;

	return error;
}
