revwalk_next_timesort(git_commit_list_node **object_out, git_revwalk *walk)
{
	int error;
	git_commit_list_node *next;

	while ((next = git_pqueue_pop(&walk->iterator_time)) != NULL)
		if (!next->uninteresting) {
			if ((error = process_commit_parents(walk, next)) < 0)
				return error;

			*object_out = next;
			return 0;
		}

	giterr_clear();
	return GIT_ITEROVER;
}
