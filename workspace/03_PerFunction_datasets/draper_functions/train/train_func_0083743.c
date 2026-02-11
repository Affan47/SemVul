get_octopus_merge_bases(struct commit_list *in)
{
	struct commit_list *i, *j, *k, *ret = NULL;
	struct commit_list **pptr = &ret;

	for (i = in; i; i = i->next) {
		if (!ret)
			pptr = &commit_list_insert(i->item, pptr)->next;
		else {
			struct commit_list *new = NULL, *end = NULL;

			for (j = ret; j; j = j->next) {
				struct commit_list *bases;
				bases = get_merge_bases(i->item, j->item, 1);
				if (!new)
					new = bases;
				else
					end->next = bases;
				for (k = bases; k; k = k->next)
					end = k;
			}
			ret = new;
		}
	}
	return ret;
}
