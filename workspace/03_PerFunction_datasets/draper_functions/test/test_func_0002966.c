process_commit(git_revwalk *walk, git_commit_list_node *commit, int hide)
{
	int error;

	if (hide)
		mark_uninteresting(commit);

	if (commit->seen)
		return 0;

	commit->seen = 1;

	if ((error = git_commit_list_parse(walk, commit)) < 0)
		return error;

	return walk->enqueue(walk, commit);
}
