packfile_refresh_all(struct pack_backend *backend)
{
	int error;
	struct stat st;
	git_buf path = GIT_BUF_INIT;

	if (backend->pack_folder == NULL)
		return 0;

	if (p_stat(backend->pack_folder, &st) < 0 || !S_ISDIR(st.st_mode))
		return git_odb__error_notfound("failed to refresh packfiles", NULL);

	git_buf_sets(&path, backend->pack_folder);


	error = git_path_direach(&path, packfile_load__cb, (void *)backend);

	git_buf_free(&path);

	if (error < 0)
		return error;

	git_vector_sort(&backend->packs);

	return 0;
}
