first_in_list(struct candidate_list *list)
{
	if (list->count == 0)
		return NULL;
	return rb_entry(rb_first(&list->rb_tree), struct gc_candidate, rb_node);
}
