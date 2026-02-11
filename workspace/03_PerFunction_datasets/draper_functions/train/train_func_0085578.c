tree_iterator__advance(
	const git_index_entry **entry, git_iterator *self)
{
	int error;
	tree_iterator *ti = (tree_iterator *)self;
	tree_iterator_frame *tf = ti->head;

	iterator__clear_entry(entry);

	if (tf->current >= tf->n_entries)
		return GIT_ITEROVER;

	if (!iterator__has_been_accessed(ti))
		return tree_iterator__current(entry, self);

	if (iterator__do_autoexpand(ti) && iterator__include_trees(ti) &&
		tree_iterator__at_tree(ti))
		return tree_iterator__advance_into(entry, self);

	if (ti->path_has_filename) {
		git_buf_rtruncate_at_char(&ti->path, '/');
		ti->path_has_filename = ti->entry_is_current = false;
	}


	while (!tree_iterator__move_to_next(ti, tf) &&
		   tree_iterator__pop_frame(ti, false))
		tf = ti->head;


	if ((error = tree_iterator__set_next(ti, tf)) < 0)
		return error;


	if (!iterator__include_trees(ti) && tree_iterator__at_tree(ti))
		return tree_iterator__advance_into(entry, self);

	return tree_iterator__current(entry, self);
}
