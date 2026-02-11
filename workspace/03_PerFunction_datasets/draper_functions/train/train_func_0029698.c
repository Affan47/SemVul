attr_cache_upsert(git_attr_cache *cache, git_attr_file *file)
{
	git_attr_file_entry *entry;
	git_attr_file *old;

	if (attr_cache_lock(cache) < 0)
		return -1;

	entry = attr_cache_lookup_entry(cache, file->entry->path);

	GIT_REFCOUNT_OWN(file, entry);
	GIT_REFCOUNT_INC(file);

	old = git__compare_and_swap(
		&entry->file[file->source], entry->file[file->source], file);

	if (old) {
		GIT_REFCOUNT_OWN(old, NULL);
		git_attr_file__free(old);
	}

	attr_cache_unlock(cache);
	return 0;
}
