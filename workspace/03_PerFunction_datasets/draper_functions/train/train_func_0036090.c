git_diff__paired_foreach(
	git_diff_list *head2idx,
	git_diff_list *idx2wd,
	int (*cb)(git_diff_delta *h2i, git_diff_delta *i2w, void *payload),
	void *payload)
{
	int cmp;
	git_diff_delta *h2i, *i2w;
	size_t i, j, i_max, j_max;
	int (*strcomp)(const char *, const char *) = git__strcmp;
	bool icase_mismatch;

	i_max = head2idx ? head2idx->deltas.length : 0;
	j_max = idx2wd ? idx2wd->deltas.length : 0;


	icase_mismatch =
		(head2idx != NULL && idx2wd != NULL &&
		 ((head2idx->opts.flags ^ idx2wd->opts.flags) & GIT_DIFF_DELTAS_ARE_ICASE));


	if (icase_mismatch) {
		if (head2idx->opts.flags & GIT_DIFF_DELTAS_ARE_ICASE) {
			git_vector_set_cmp(&head2idx->deltas, git_diff_delta__cmp);
			git_vector_sort(&head2idx->deltas);
		} else {
			git_vector_set_cmp(&idx2wd->deltas, git_diff_delta__cmp);
			git_vector_sort(&idx2wd->deltas);
		}
	}
	else if (head2idx != NULL && head2idx->opts.flags & GIT_DIFF_DELTAS_ARE_ICASE)
		strcomp = git__strcasecmp;

	for (i = 0, j = 0; i < i_max || j < j_max; ) {
		h2i = head2idx ? GIT_VECTOR_GET(&head2idx->deltas, i) : NULL;
		i2w = idx2wd ? GIT_VECTOR_GET(&idx2wd->deltas, j) : NULL;

		cmp = !i2w ? -1 : !h2i ? 1 :
			strcomp(h2i->new_file.path, i2w->old_file.path);

		if (cmp < 0) {
			if (cb(h2i, NULL, payload))
				return GIT_EUSER;
			i++;
		} else if (cmp > 0) {
			if (cb(NULL, i2w, payload))
				return GIT_EUSER;
			j++;
		} else {
			if (cb(h2i, i2w, payload))
				return GIT_EUSER;
			i++; j++;
		}
	}


	if (icase_mismatch) {
		if (head2idx->opts.flags & GIT_DIFF_DELTAS_ARE_ICASE) {
			git_vector_set_cmp(&head2idx->deltas, git_diff_delta__casecmp);
			git_vector_sort(&head2idx->deltas);
		} else {
			git_vector_set_cmp(&idx2wd->deltas, git_diff_delta__casecmp);
			git_vector_sort(&idx2wd->deltas);
		}
	}

	return 0;
}
