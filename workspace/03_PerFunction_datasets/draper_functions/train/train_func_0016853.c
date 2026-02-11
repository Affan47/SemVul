ahead_behind(git_commit_list_node *one, git_commit_list_node *two,
	size_t *ahead, size_t *behind)
{
	git_commit_list_node *commit;
	git_pqueue pq;
	int i;
	*ahead = 0;
	*behind = 0;

	if (git_pqueue_init(&pq, 2, git_commit_list_time_cmp) < 0)
		return -1;
	if (git_pqueue_insert(&pq, one) < 0)
		goto on_error;
	if (git_pqueue_insert(&pq, two) < 0)
		goto on_error;

	while ((commit = git_pqueue_pop(&pq)) != NULL) {
		if (commit->flags & RESULT ||
			(commit->flags & (PARENT1 | PARENT2)) == (PARENT1 | PARENT2))
			continue;
		else if (commit->flags & PARENT1)
			(*behind)++;
		else if (commit->flags & PARENT2)
			(*ahead)++;

		for (i = 0; i < commit->out_degree; i++) {
			git_commit_list_node *p = commit->parents[i];
			if (git_pqueue_insert(&pq, p) < 0)
				return -1;
		}
		commit->flags |= RESULT;
	}

	git_pqueue_free(&pq);
	return 0;

on_error:
	git_pqueue_free(&pq);
	return -1;
}
