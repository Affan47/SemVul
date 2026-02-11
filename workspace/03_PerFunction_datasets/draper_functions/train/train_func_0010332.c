quickcheck_repository_dir(const char *repository_path)
{
	char path_aux[GIT_PATH_MAX];


	git_path_join(path_aux, repository_path, GIT_HEAD_FILE);
	if (git_futils_isfile(path_aux) < 0)
		return GIT_ERROR;

	git_path_join(path_aux, repository_path, GIT_OBJECTS_DIR);
	if (git_futils_isdir(path_aux) < 0)
		return GIT_ERROR;

	git_path_join(path_aux, repository_path, GIT_REFS_DIR);
	if (git_futils_isdir(path_aux) < 0)
		return GIT_ERROR;

	return GIT_SUCCESS;
}
