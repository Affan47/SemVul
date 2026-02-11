config_refresh(git_config_backend *cfg)
{
	int error = 0, updated = 0, any_updated = 0;
	diskfile_backend *b = (diskfile_backend *)cfg;
	struct reader *reader = NULL;
	uint32_t i;

	for (i = 0; i < git_array_size(b->readers); i++) {
		reader = git_array_get(b->readers, i);
		error = git_futils_readbuffer_updated(
			&reader->buffer, reader->file_path,
			&reader->file_mtime, &reader->file_size, &updated);

		if (error < 0 && error != GIT_ENOTFOUND)
			return error;

		if (updated)
			any_updated = 1;
	}

	if (!any_updated)
		return (error == GIT_ENOTFOUND) ? 0 : error;

	return config__refresh(cfg);
}
