loose_write(git_reference *ref)
{
	git_filebuf file;
	char ref_path[GIT_PATH_MAX];
	int error;
	struct stat st;

	git_path_join(ref_path, ref->owner->path_repository, ref->name);

	if ((error = git_filebuf_open(&file, ref_path, GIT_FILEBUF_FORCE)) < GIT_SUCCESS)
		return git__rethrow(error, "Failed to write loose reference");

	if (ref->type & GIT_REF_OID) {
		reference_oid *ref_oid = (reference_oid *)ref;
		char oid[GIT_OID_HEXSZ + 1];

		memset(oid, 0x0, sizeof(oid));

		git_oid_fmt(oid, &ref_oid->oid);
		error = git_filebuf_printf(&file, "%s\n", oid);
		if (error < GIT_SUCCESS)
			goto unlock;

	} else if (ref->type & GIT_REF_SYMBOLIC) {
		reference_symbolic *ref_sym = (reference_symbolic *)ref;

		error = git_filebuf_printf(&file, GIT_SYMREF "%s\n", ref_sym->target);
	} else {
		error = git__throw(GIT_EOBJCORRUPTED, "Failed to write reference. Invalid reference type");
		goto unlock;
	}

	error = git_filebuf_commit(&file);

	if (p_stat(ref_path, &st) == GIT_SUCCESS)
		ref->mtime = st.st_mtime;

	return error == GIT_SUCCESS ? GIT_SUCCESS : git__rethrow(error, "Failed to write loose reference");

unlock:
	git_filebuf_cleanup(&file);
	return error == GIT_SUCCESS ? GIT_SUCCESS : git__rethrow(error, "Failed to write loose reference");
}
