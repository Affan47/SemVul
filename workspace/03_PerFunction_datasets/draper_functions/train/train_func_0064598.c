push_commit(git_revwalk *walk, const git_oid *oid, int uninteresting)
{
	commit_object *commit;

	commit = commit_lookup(walk, oid);
	if (commit == NULL)
		return git__throw(GIT_ENOTFOUND, "Failed to push commit. Object not found");

	commit->uninteresting = uninteresting;

	return process_commit(walk, commit);
}
