git_attr_cache__get(
	git_attr_file **out,
	git_repository *repo,
	git_attr_file_source source,
	const char *base,
	const char *filename,
	git_attr_file_parser parser)
{
	int error = 0;
	git_attr_cache *cache = git_repository_attr_cache(repo);
	git_attr_file_entry *entry = NULL;
	git_attr_file *file = NULL, *updated = NULL;

	if ((error = attr_cache_lookup(
			&file, &entry, repo, source, base, filename)) < 0)
		return error;


	if (!file || (error = git_attr_file__out_of_date(repo, file)) > 0)
		error = git_attr_file__load(&updated, repo, entry, source, parser);


	if (updated) {
		if ((error = attr_cache_upsert(cache, updated)) < 0)
			git_attr_file__free(updated);
		else {
			git_attr_file__free(file);
			file = updated;
		}
	}


	if (error < 0) {

		if (file) {
			attr_cache_remove(cache, file);
			git_attr_file__free(file);
			file = NULL;
		}

		if (error == GIT_ENOTFOUND) {
			giterr_clear();
			error = 0;
		}
	}

	*out = file;
	return error;
}
