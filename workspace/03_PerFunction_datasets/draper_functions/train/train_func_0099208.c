git_reference_name_to_id(
	git_oid *out, git_repository *repo, const char *name)
{
	int error;
	git_reference *ref;

	if ((error = git_reference_lookup_resolved(&ref, repo, name, -1)) < 0)
		return error;

	git_oid_cpy(out, git_reference_target(ref));
	git_reference_free(ref);
	return 0;
}
