tree_iterator__current(
	const git_index_entry **entry, git_iterator *self)
{
	tree_iterator *ti = (tree_iterator *)self;
	tree_iterator_frame *tf = ti->head;
	const git_tree_entry *te;

	iterator__clear_entry(entry);

	if (tf->current >= tf->n_entries)
		return 0;
	te = tf->entries[tf->current]->te;

	ti->entry.mode = te->attr;
	git_oid_cpy(&ti->entry.oid, &te->oid);

	ti->entry.path = tree_iterator__current_filename(ti, te);
	GITERR_CHECK_ALLOC(ti->entry.path);

	if (ti->path_ambiguities > 0)
		tree_iterator__rewrite_filename(ti);

	if (iterator__past_end(ti, ti->entry.path))
		return tree_iterator__pop_all(ti, true, false);

	if (entry)
		*entry = &ti->entry;

	return 0;
}
