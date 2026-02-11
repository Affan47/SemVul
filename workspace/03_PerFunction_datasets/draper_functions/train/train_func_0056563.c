tree_iterator__set_next(tree_iterator *ti, tree_iterator_frame *tf)
{
	int error;
	const git_tree_entry *te, *last = NULL;

	tf->next = tf->current;

	for (; tf->next < tf->n_entries; tf->next++, last = te) {
		te = tf->entries[tf->next]->te;

		if (last && tree_iterator__te_cmp(last, te, ti->strncomp))
			break;


		if (git_tree_entry__is_tree(te) &&
			(error = git_tree_lookup(
				&tf->entries[tf->next]->tree, ti->base.repo, &te->oid)) < 0)
			return error;
	}

	if (tf->next > tf->current + 1)
		ti->path_ambiguities++;

	if (last && !tree_iterator__current_filename(ti, last))
		return -1;

	return 0;
}
