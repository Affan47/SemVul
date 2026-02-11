hm_linklist_get(const hm_linklist_t *l, const char *key){
	if (key == NULL)
		return NULL;

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *data = node->data;

		const int cmp = strcmp(hm_listdata_getkey(data), key);

		if (cmp == 0)
			return data;

		if (cmp > 0)
			break;
	}

	return NULL;
}
