packed_parse_oid(
		reference_oid **ref_out,
		git_repository *repo,
		const char **buffer_out,
		const char *buffer_end)
{
	reference_oid *ref = NULL;

	const char *buffer = *buffer_out;
	const char *refname_begin, *refname_end;

	int error = GIT_SUCCESS;
	int refname_len;
	char refname[GIT_REFNAME_MAX];
	git_oid id;

	refname_begin = (buffer + GIT_OID_HEXSZ + 1);
	if (refname_begin >= buffer_end ||
		refname_begin[-1] != ' ') {
		error = GIT_EPACKEDREFSCORRUPTED;
		goto cleanup;
	}


	if ((error = git_oid_fromstr(&id, buffer)) < GIT_SUCCESS)
		goto cleanup;

	refname_end = memchr(refname_begin, '\n', buffer_end - refname_begin);
	if (refname_end == NULL) {
		error = GIT_EPACKEDREFSCORRUPTED;
		goto cleanup;
	}

	refname_len = refname_end - refname_begin;

	memcpy(refname, refname_begin, refname_len);
	refname[refname_len] = 0;

	if (refname[refname_len - 1] == '\r')
		refname[refname_len - 1] = 0;

	error = reference_create((git_reference **)&ref, repo, refname, GIT_REF_OID);
	if (error < GIT_SUCCESS)
		goto cleanup;

	git_oid_cpy(&ref->oid, &id);
	ref->ref.type |= GIT_REF_PACKED;

	*ref_out = ref;
	*buffer_out = refname_end + 1;

	return GIT_SUCCESS;

cleanup:
	reference_free((git_reference *)ref);
	return error == GIT_SUCCESS ? GIT_SUCCESS : git__rethrow(error, "Failed to parse OID of packed reference");
}
