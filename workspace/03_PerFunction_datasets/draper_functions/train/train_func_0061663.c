_dirent_loose_load(void *data, char *full_path)
{
	git_repository *repository = (git_repository *)data;
	git_reference *reference, *old_ref;
	char *file_path;
	int error;

	if (gitfo_isdir(full_path) == GIT_SUCCESS)
		return gitfo_dirent(full_path, GIT_PATH_MAX, _dirent_loose_load, repository);

	file_path = full_path + strlen(repository->path_repository);
	error = loose_lookup(&reference, repository, file_path, 1);
	if (error == GIT_SUCCESS && reference != NULL) {
		reference->type |= GIT_REF_PACKED;

		if (git_hashtable_insert2(repository->references.packfile, reference->name, reference, (void **)&old_ref) < GIT_SUCCESS) {
			reference_free(reference);
			return GIT_ENOMEM;
		}

		if (old_ref != NULL)
			reference_free(old_ref);
	}

	return error == GIT_SUCCESS ? GIT_SUCCESS : git__rethrow(error, "Failed to load loose dirent");
}
