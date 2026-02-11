reference_create_symbolic(git_reference **ref_out, git_repository *repo, const char *name, const char *target, int force)
{
	char normalized[MAX_GITDIR_TREE_STRUCTURE_PATH_LENGTH];
	int error = GIT_SUCCESS, updated = 0;
	git_reference *ref = NULL, *old_ref = NULL;

	if (git_reference_lookup(&ref, repo, name) == GIT_SUCCESS && !force)
		return git__throw(GIT_EEXISTS, "Failed to create symbolic reference. Reference already exists");


	if (ref && ref->type & GIT_REF_SYMBOLIC){
		updated = 1;
	} else {
		ref = NULL;
		error = reference_create(&ref, repo, name, GIT_REF_SYMBOLIC);
		if (error < GIT_SUCCESS)
			goto cleanup;
	}


	error = normalize_name(normalized, target, 0);
	if (error < GIT_SUCCESS)
		goto cleanup;


	error = git_reference_set_target(ref, normalized);
	if (error < GIT_SUCCESS)
		goto cleanup;


	if (!updated){
		error = git_hashtable_insert2(repo->references.loose_cache, ref->name, ref, (void **) &old_ref);
		if (error < GIT_SUCCESS)
			goto cleanup;

		if(old_ref)
			reference_free(old_ref);
	}

	*ref_out = ref;

	return error == GIT_SUCCESS ? GIT_SUCCESS : git__rethrow(error, "Failed to create symbolic reference");

cleanup:
	reference_free(ref);
	return error == GIT_SUCCESS ? GIT_SUCCESS : git__rethrow(error, "Failed to create symbolic reference");
}
