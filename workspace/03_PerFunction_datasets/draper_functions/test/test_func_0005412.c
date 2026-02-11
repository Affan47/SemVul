git_stash_foreach(
	git_repository *repo,
	git_stash_cb callback,
	void *payload)
{
	git_reference *stash;
	git_reflog *reflog = NULL;
	int error;
	size_t i, max;
	const git_reflog_entry *entry;

	error = git_reference_lookup(&stash, repo, GIT_REFS_STASH_FILE);
	if (error == GIT_ENOTFOUND) {
		giterr_clear();
		return 0;
	}
	if (error < 0)
		goto cleanup;

	if ((error = git_reflog_read(&reflog, stash)) < 0)
		goto cleanup;

	max = git_reflog_entrycount(reflog);
	for (i = 0; i < max; i++) {
		entry = git_reflog_entry_byindex(reflog, i);

		if (callback(i,
			git_reflog_entry_message(entry),
			git_reflog_entry_id_new(entry),
			payload)) {
				error = GIT_EUSER;
				break;
		}
	}

cleanup:
	git_reference_free(stash);
	git_reflog_free(reflog);
	return error;
}
