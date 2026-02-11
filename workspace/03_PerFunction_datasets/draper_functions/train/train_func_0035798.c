lt_mem_slist_append(lt_mem_slist_t    *list,
		    lt_pointer_t       key,
		    lt_destroy_func_t  func)
{
	lt_mem_slist_t *l = lt_mem_slist_new();
	lt_mem_slist_t *last;

	l->key = key;
	l->func = func;
	l->next = NULL;
	if (list) {
		last = lt_mem_slist_last(list);
		last->next = l;
	} else {
		list = l;
	}

	return list;
}
