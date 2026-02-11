git_reference_foreach_glob(
	git_repository *repo,
	const char *glob,
	git_reference_foreach_name_cb callback,
	void *payload)
{
	git_reference_iterator *iter;
	const char *refname;
	int error;

	if (git_reference_iterator_glob_new(&iter, repo, glob) < 0)
		return -1;

	while ((error = git_reference_next_name(&refname, iter)) == 0) {
		if (callback(refname, payload)) {
			error = GIT_EUSER;
			goto out;
		}
	}

	if (error == GIT_ITEROVER)
		error = 0;

out:
	git_reference_iterator_free(iter);
	return error;
}
