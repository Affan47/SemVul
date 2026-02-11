loose_write(git_reference *ref)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	git_buf ref_path = GIT_BUF_INIT;
	struct stat st;

	if (git_buf_joinpath(&ref_path, ref->owner->path_repository, ref->name) < 0)
		return -1;


	if (git_path_isdir(git_buf_cstr(&ref_path)) &&
		(git_futils_rmdir_r(git_buf_cstr(&ref_path), GIT_DIRREMOVAL_ONLY_EMPTY_DIRS) < 0)) {
			git_buf_free(&ref_path);
			return -1;
		}

	if (git_filebuf_open(&file, ref_path.ptr, GIT_FILEBUF_FORCE) < 0) {
		git_buf_free(&ref_path);
		return -1;
	}

	git_buf_free(&ref_path);

	if (ref->flags & GIT_REF_OID) {
		char oid[GIT_OID_HEXSZ + 1];

		git_oid_fmt(oid, &ref->target.oid);
		oid[GIT_OID_HEXSZ] = '\0';

		git_filebuf_printf(&file, "%s\n", oid);

	} else if (ref->flags & GIT_REF_SYMBOLIC) {
		git_filebuf_printf(&file, GIT_SYMREF "%s\n", ref->target.symbolic);
	} else {
		assert(0);
	}

	if (p_stat(ref_path.ptr, &st) == 0)
		ref->mtime = st.st_mtime;

	return git_filebuf_commit(&file, GIT_REFS_FILE_MODE);
}
