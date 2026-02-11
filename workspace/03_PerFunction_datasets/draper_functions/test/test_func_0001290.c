gitrp_push(git_revpool *pool, git_commit *commit)
{
	if (commit == NULL || commit->seen)
		return GIT_ENOTFOUND;

	if (commit->object.pool != pool || pool->walking)
		return GIT_ERROR;

	if (!commit->parsed) {
		int error = git_commit_parse_existing(commit);
		if (error < 0)
			return error;
	}


	if (commit->uninteresting)
		git_commit__mark_uninteresting(commit);

	if (git_commit_list_push_back(&pool->roots, commit) < 0)
		return GIT_ENOMEM;

	return 0;
}
