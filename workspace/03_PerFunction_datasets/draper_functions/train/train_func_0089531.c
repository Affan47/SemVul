process_commit_parents(git_revwalk *walk, git_commit_list_node *commit)
{
	unsigned short i;
	int error = 0;

	for (i = 0; i < commit->out_degree && !error; ++i)
		error = process_commit(walk, commit->parents[i], commit->uninteresting);

	return error;
}
