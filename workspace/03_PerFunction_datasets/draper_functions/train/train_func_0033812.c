branch_compare(const void *l1, const void *l2)
{
	const struct branch *branch1 = ((const struct line *) l1)->data;
	const struct branch *branch2 = ((const struct line *) l2)->data;

	if (branch1->ref == &branch_all)
		return -1;
	else if (branch2->ref == &branch_all)
		return 1;

	switch (get_sort_field(branch_sort_state)) {
	case ORDERBY_DATE:
		return sort_order(branch_sort_state, timecmp(&branch1->time, &branch2->time));

	case ORDERBY_AUTHOR:
		return sort_order(branch_sort_state, strcmp(branch1->author, branch2->author));

	case ORDERBY_NAME:
	default:
		return sort_order(branch_sort_state, strcmp(branch1->ref->name, branch2->ref->name));
	}
}
