loose_lookup_to_packfile(
	struct packref **ref_out,
	refdb_fs_backend *backend,
	const char *name)
{
	git_buf ref_file = GIT_BUF_INIT;
	struct packref *ref = NULL;
	size_t name_len;

	*ref_out = NULL;

	if (reference_read(&ref_file, NULL, backend->path, name, NULL) < 0)
		return -1;

	git_buf_rtrim(&ref_file);

	name_len = strlen(name);
	ref = git__malloc(sizeof(struct packref) + name_len + 1);
	GITERR_CHECK_ALLOC(ref);

	memcpy(ref->name, name, name_len);
	ref->name[name_len] = 0;

	if (loose_parse_oid(&ref->oid, name, &ref_file) < 0) {
		git_buf_free(&ref_file);
		git__free(ref);
		return -1;
	}

	ref->flags = PACKREF_WAS_LOOSE;

	*ref_out = ref;
	git_buf_free(&ref_file);
	return 0;
}
