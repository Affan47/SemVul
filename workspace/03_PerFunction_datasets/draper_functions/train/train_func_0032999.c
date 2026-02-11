packed_load(git_repository *repo)
{
	int error = GIT_SUCCESS;
	git_fbuffer packfile = GIT_FBUFFER_INIT;
	const char *buffer_start, *buffer_end;
	git_refcache *ref_cache = &repo->references;


	if (repo->references.packfile != NULL) {
		time_t packed_time;


		if (!reference_read(NULL, &packed_time, repo->path_repository, GIT_PACKEDREFS_FILE) &&
			packed_time == ref_cache->packfile_time)
			return GIT_SUCCESS;

		git_hashtable_clear(repo->references.packfile);
	} else {
		ref_cache->packfile = git_hashtable_alloc(
			default_table_size,
			reftable_hash,
			(git_hash_keyeq_ptr)strcmp);

		if (ref_cache->packfile == NULL)
			return GIT_ENOMEM;
	}


	error = reference_read(
			&packfile,
			&ref_cache->packfile_time,
			repo->path_repository,
			GIT_PACKEDREFS_FILE);


	if (error == GIT_ENOTFOUND)
		return GIT_SUCCESS;

	if (error < GIT_SUCCESS)
		goto cleanup;

	buffer_start = (const char *)packfile.data;
	buffer_end = (const char *)(buffer_start) + packfile.len;

	while (buffer_start < buffer_end && buffer_start[0] == '#') {
		buffer_start = strchr(buffer_start, '\n');
		if (buffer_start == NULL) {
			error = GIT_EPACKEDREFSCORRUPTED;
			goto cleanup;
		}
		buffer_start++;
	}

	while (buffer_start < buffer_end) {
		reference_oid *ref = NULL;

		error = packed_parse_oid(&ref, repo, &buffer_start, buffer_end);
		if (error < GIT_SUCCESS)
			goto cleanup;

		if (buffer_start[0] == '^') {
			error = packed_parse_peel(ref, &buffer_start, buffer_end);
			if (error < GIT_SUCCESS)
				goto cleanup;
		}

		error = git_hashtable_insert(ref_cache->packfile, ref->ref.name, ref);
		if (error < GIT_SUCCESS) {
			reference_free((git_reference *)ref);
			goto cleanup;
		}
	}

	git_futils_freebuffer(&packfile);
	return GIT_SUCCESS;

cleanup:
	git_hashtable_free(ref_cache->packfile);
	ref_cache->packfile = NULL;
	git_futils_freebuffer(&packfile);
	return error == GIT_SUCCESS ? GIT_SUCCESS : git__rethrow(error, "Failed to load packed references");
}
