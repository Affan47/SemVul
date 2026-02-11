load_attr_blob_from_index(
	const char **content,
	git_blob **blob,
	git_repository *repo,
	const git_oid *old_oid,
	const char *relfile)
{
	int error;
	git_index *index;
	git_index_entry *entry;

	if ((error = git_repository_index__weakptr(&index, repo)) < 0 ||
		(error = git_index_find(index, relfile)) < 0)
		return error;

	entry = git_index_get_byindex(index, error);

	if (old_oid && git_oid_cmp(old_oid, &entry->oid) == 0)
		return GIT_ENOTFOUND;

	if ((error = git_blob_lookup(blob, repo, &entry->oid)) < 0)
		return error;

	*content = git_blob_rawcontent(*blob);
	return 0;
}
