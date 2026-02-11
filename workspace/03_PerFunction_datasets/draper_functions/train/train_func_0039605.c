packed_write_ref(reference_oid *ref, git_filebuf *file)
{
	int error;
	char oid[GIT_OID_HEXSZ + 1];

	git_oid_fmt(oid, &ref->oid);
	oid[GIT_OID_HEXSZ] = 0;


	if (ref->ref.type & GIT_REF_HAS_PEEL) {
		char peel[GIT_OID_HEXSZ + 1];
		git_oid_fmt(peel, &ref->peel_target);
		peel[GIT_OID_HEXSZ] = 0;

		error = git_filebuf_printf(file, "%s %s\n^%s\n", oid, ref->ref.name, peel);
	} else {
		error = git_filebuf_printf(file, "%s %s\n", oid, ref->ref.name);
	}

	return error;
}
