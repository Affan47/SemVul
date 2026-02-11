lt_mem_slist_delete(lt_mem_slist_t *list,
		    lt_pointer_t   *data)
{
	lt_mem_slist_t *l = list;

	while (l) {
		if (l->key == data) {
			list = lt_mem_slist_delete_link(list, l);
			break;
		} else {
			l = l->next;
		}
	}

	return list;
}
