loose_lookup_to_packfile(refdb_fs_backend *backend, const char *name)
{
	int error = 0;
	git_buf ref_file = GIT_BUF_INIT;
	struct packref *ref = NULL;
	git_oid oid;


	if (loose_readbuffer(&ref_file, backend->path, name) < 0) {
		giterr_clear();
		goto done;
	}


	if (!git__prefixcmp(git_buf_cstr(&ref_file), GIT_SYMREF))
		goto done;


	if ((error = loose_parse_oid(&oid, name, &ref_file)) < 0)
		goto done;

	git_sortedcache_wlock(backend->refcache);

	if (!(error = git_sortedcache_upsert(
			(void **)&ref, backend->refcache, name))) {

		git_oid_cpy(&ref->oid, &oid);
		ref->flags = PACKREF_WAS_LOOSE;
	}

	git_sortedcache_wunlock(backend->refcache);

done:
	git_buf_free(&ref_file);
	return error;
}
