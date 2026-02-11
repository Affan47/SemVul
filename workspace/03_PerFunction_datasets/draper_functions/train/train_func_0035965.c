_hm_skiplist_locate(const hm_skiplist_t *l, const char *key, int complete_evaluation){

	if (key == NULL){
		hm_error("FATAL ERROR", __FILE__, __LINE__);
	}


	int cmp = 1;

	const hm_skiplist_node_t *node = NULL;
	const hm_skiplist_node_t *prev = NULL;

	hm_skiplist_height_t height = l->height;
	while(height){
		node = prev ? prev : l->heads[height - 1];

		while(node){
			cmp = strcmp(hm_listdata_getkey(node->data), key);

			if (cmp >= 0)
				break;

			prev = node;
			node = node->next[height - 1];
		}


		if (cmp == 0 && complete_evaluation == 0)
			return node;

		l->loc[height - 1] = (void *) prev;

		height--;
	}

	return cmp ? NULL : node;
}
