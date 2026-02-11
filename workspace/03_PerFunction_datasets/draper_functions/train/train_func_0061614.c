premark_uninteresting(git_revwalk *walk)
{
	int error = 0;
	unsigned short i;
	git_pqueue q;
	git_commit_list *list;
	git_commit_list_node *commit, *parent;

	if ((error = git_pqueue_init(&q, 0, 8, git_commit_list_time_cmp)) < 0)
		return error;

	for (list = walk->user_input; list; list = list->next) {
		if ((error = git_commit_list_parse(walk, list->item)) < 0)
			goto cleanup;

		if ((error = git_pqueue_insert(&q, list->item)) < 0)
			goto cleanup;
	}

	while (interesting(&q)) {
		commit = git_pqueue_pop(&q);

		for (i = 0; i < commit->out_degree; i++) {
			parent = commit->parents[i];

			if ((error = git_commit_list_parse(walk, parent)) < 0)
				goto cleanup;

			if (commit->uninteresting)
				parent->uninteresting = 1;

			if (contains(&q, parent))
				continue;

			if ((error = git_pqueue_insert(&q, parent)) < 0)
				goto cleanup;
		}
	}

cleanup:
	git_pqueue_free(&q);
	return error;
}
