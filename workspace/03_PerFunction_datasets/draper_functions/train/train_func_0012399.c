Vect_list_append(struct ilist *list, int val)
{
    int i;
    size_t size;

    if (list == NULL)
	return 1;

    for (i = 0; i < list->n_values; i++) {
	if (val == list->value[i])
	    return 0;
    }

    if (list->n_values == list->alloc_values) {
	size = (list->n_values + 1000) * sizeof(int);
	list->value = (int *)G_realloc((void *)list->value, size);
	list->alloc_values = list->n_values + 1000;
    }

    list->value[list->n_values] = val;
    list->n_values++;

    return 0;
}
