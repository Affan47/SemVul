reference_can_write(
	git_repository *repo,
	const char *refname,
	const char *previous_name,
	int force)
{


	if (reference_path_available(repo, refname, previous_name) < 0)
		return -1;


	if (!force) {
		int exists;

		if (reference_exists(&exists, repo, refname) < 0)
			return -1;


		if (exists) {
			giterr_set(GITERR_REFERENCE,
				"A reference with that name (%s) already exists", refname);
			return GIT_EEXISTS;
		}
	}


	return 0;
}
