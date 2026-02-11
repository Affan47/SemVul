find_unique_abbrev_size(
	int *out,
	git_repository *repo,
	const git_oid *oid_in,
	int abbreviated_size)
{
	size_t size = abbreviated_size;
	git_odb *odb;
	git_oid dummy;
	int error;

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0)
		return error;

	while (size < GIT_OID_HEXSZ) {
		if ((error = git_odb_exists_prefix(&dummy, odb, oid_in, size)) == 0) {
			*out = (int) size;
			return 0;
		}


		if (error != GIT_EAMBIGUOUS)
			return error;


		size++;
	}


	*out = GIT_OID_HEXSZ;

	return 0;
}
