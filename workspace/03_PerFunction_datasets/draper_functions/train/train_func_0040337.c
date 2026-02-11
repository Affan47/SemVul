spoolandsort_iterator__current(
	git_iterator *self, const git_index_entry **entry)
{
	spoolandsort_iterator *si = (spoolandsort_iterator *)self;

	if (si->position < si->entries.length)
		*entry = (const git_index_entry *)git_vector_get_const(&si->entries, si->position);
	else
		*entry = NULL;

	return 0;
}
