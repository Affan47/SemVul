reference_create(
	git_reference **ref_out,
	git_repository *repo,
	const char *name,
	git_rtype type)
{
	char normalized[MAX_GITDIR_TREE_STRUCTURE_PATH_LENGTH];
	int error = GIT_SUCCESS, size;
	git_reference *reference = NULL;

	assert(ref_out && repo && name);

	if (type == GIT_REF_SYMBOLIC)
		size = sizeof(reference_symbolic);
	else if (type == GIT_REF_OID)
		size = sizeof(reference_oid);
	else
		return GIT_EINVALIDREFSTATE;

	reference = git__malloc(size);
	if (reference == NULL)
		return GIT_ENOMEM;

	memset(reference, 0x0, size);
	reference->owner = repo;
	reference->type = type;

	error = normalize_name(normalized, name, (type & GIT_REF_OID));
	if (error < GIT_SUCCESS)
		goto cleanup;

	reference->name = git__strdup(normalized);
	if (reference->name == NULL) {
		error = GIT_ENOMEM;
		goto cleanup;
	}

	*ref_out = reference;

	return error;

cleanup:
	reference_free(reference);
	return error;
}
