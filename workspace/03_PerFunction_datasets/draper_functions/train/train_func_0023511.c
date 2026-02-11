loose_update(git_reference *ref)
{
	int error;
	time_t ref_time;
	gitfo_buf ref_file = GITFO_BUF_INIT;

	if (ref->type & GIT_REF_PACKED)
		return packed_load(ref->owner);

	error = reference_read(NULL, &ref_time, ref->owner->path_repository, ref->name);
	if (error < GIT_SUCCESS)
		goto cleanup;

	if (ref_time == ref->mtime)
		return GIT_SUCCESS;

	error = reference_read(&ref_file, &ref->mtime, ref->owner->path_repository, ref->name);
	if (error < GIT_SUCCESS)
		goto cleanup;

	if (ref->type == GIT_REF_SYMBOLIC)
		error = loose_parse_symbolic(ref, &ref_file);
	else if (ref->type == GIT_REF_OID)
		error = loose_parse_oid(ref, &ref_file);
	else
		error = git__throw(GIT_EOBJCORRUPTED,
			"Invalid reference type (%d) for loose reference", ref->type);

	gitfo_free_buf(&ref_file);

cleanup:
	if (error != GIT_SUCCESS) {
		reference_free(ref);
		git_hashtable_remove(ref->owner->references.loose_cache, ref->name);
	}

	return error;
}
