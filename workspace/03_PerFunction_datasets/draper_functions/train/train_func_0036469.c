git_config_get_entry(const git_config_entry **out, const git_config *cfg, const char *name)
{
	file_internal *internal;
	unsigned int i;

	*out = NULL;

	git_vector_foreach(&cfg->files, i, internal) {
		git_config_backend *file = internal->file;
		int ret = file->get(file, name, out);
		if (ret != GIT_ENOTFOUND)
			return ret;
	}

	return config_error_notfound(name);
}
