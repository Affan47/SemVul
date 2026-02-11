git_reflog_rename(git_repository *repo, const char *old_name, const char *new_name)
{
	git_refdb *refdb;
	int error;

	if ((error = git_repository_refdb__weakptr(&refdb, repo)) < 0)
		return -1;

	return refdb->backend->reflog_rename(refdb->backend, old_name, new_name);
}
