get_ref_list(const char *id)
{
	struct ref_list *list;
	size_t i;

	for (i = 0; i < ref_lists_size; i++)
		if (!strcmp(id, ref_lists[i]->id))
			return ref_lists[i];

	if (!realloc_ref_lists(&ref_lists, ref_lists_size, 1))
		return NULL;
	list = calloc(1, sizeof(*list));
	if (!list)
		return NULL;

	for (i = 0; i < refs_size; i++) {
		if (!strcmp(id, refs[i]->id) &&
		    realloc_refs_list(&list->refs, list->size, 1))
			list->refs[list->size++] = refs[i];
	}

	if (!list->refs) {
		free(list);
		return NULL;
	}

	qsort(list->refs, list->size, sizeof(*list->refs), compare_refs);
	ref_lists[ref_lists_size++] = list;
	return list;
}
