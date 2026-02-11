push_commit(git_revwalk *walk, const git_oid *oid, int uninteresting)
{
	commit_object *commit;

	commit = commit_lookup(walk, oid);
	if (commit == NULL)
		return -1;

	commit->uninteresting = uninteresting;
	if (walk->one == NULL && !uninteresting) {
		walk->one = commit;
	} else {
		if (git_vector_insert(&walk->twos, commit) < 0)
			return -1;
	}

	return 0;
}
