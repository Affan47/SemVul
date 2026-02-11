hm_linklist_put(hm_linklist_t *l, void *newdata){
	if (newdata == NULL)
		return 0;

	const char *key = hm_listdata_getkey(newdata);

	hm_linklist_node_t *prev = NULL;
	hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *olddata = node->data;

		const int cmp = strcmp(hm_listdata_getkey(olddata), key);

		if (cmp == 0){


			if (! hm_listdata_valid(newdata, olddata)){

				hm_listdata_free(newdata);
				return 0;
			}

			l->datasize = l->datasize
				- hm_listdata_sizeof(node->data)
				+ hm_listdata_sizeof(newdata);

			hm_listdata_free(node->data);
			node->data = newdata;

			return 1;
		}

		if (cmp > 0)
			break;

		prev = node;
	}

	hm_linklist_node_t *newnode = malloc(sizeof(hm_linklist_node_t));
	if (newnode == NULL){

		hm_listdata_free(newdata);
		return 0;
	}

	newnode->data = newdata;


	if (prev){

		newnode->next = prev->next;
		prev->next = newnode;
	}else{
		newnode->next = l->head;
		l->head = newnode;
	}

	l->datasize += hm_listdata_sizeof(newdata);
	l->datacount++;

	return 1;
}
