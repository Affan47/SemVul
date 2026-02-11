reflog_init(git_reflog **reflog, git_reference *ref)
{
	git_reflog *log;

	*reflog = NULL;

	log = git__malloc(sizeof(git_reflog));
	if (log == NULL)
		return GIT_ENOMEM;

	memset(log, 0x0, sizeof(git_reflog));

	log->ref_name = git__strdup(ref->name);

	if (git_vector_init(&log->entries, 0, NULL) < 0) {
		free(log->ref_name);
		free(log);
		return GIT_ENOMEM;
	}

	*reflog = log;

	return GIT_SUCCESS;
}
