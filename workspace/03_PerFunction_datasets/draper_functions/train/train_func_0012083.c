_grecs_list_eq(struct grecs_value *a, struct grecs_value *b)
{
	struct grecs_list_entry *aent, *bent;
	if (grecs_list_size(a->v.list) != grecs_list_size(b->v.list))
		return 0;

	for (aent = a->v.list->head, bent = b->v.list->head;;
	     aent = aent->next, bent = bent->next) {
		if (!aent)
			return bent == NULL;
		if (!bent)
			return 0;
		if (!grecs_value_eq(aent->data, bent->data))
			return 0;
	}

	return 1;
}
