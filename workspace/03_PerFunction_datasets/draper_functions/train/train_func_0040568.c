try_remove_existing_file_internal(
	git_config *cfg,
	git_config_level_t level)
{
	int pos = -1;
	file_internal *internal;
	size_t i;

	git_vector_foreach(&cfg->files, i, internal) {
		if (internal->level == level)
			pos = (int)i;
	}

	if (pos == -1)
		return;

	internal = git_vector_get(&cfg->files, pos);

	if (git_vector_remove(&cfg->files, pos) < 0)
		return;

	GIT_REFCOUNT_DEC(internal, file_internal_free);
}
