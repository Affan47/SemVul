node_list_remove(node_list_t* list, node_t* node) {
	if (!list || !node) return -1;
	if (list->count == 0) return -1;

	int index = 0;
	node_t* n;
	for (n = list->begin; n; n = n->next) {
		if (node == n) {
			node_t* newnode = node->next;
			if (node->prev) {
				node->prev->next = newnode;
				if (newnode) {
					newnode->prev = node->prev;
				} else {

					list->end = node->prev;
				}
			} else {

				if (newnode) {
					newnode->prev = NULL;
				}
				list->begin = newnode;
			}
			list->count--;
			return index;
		}
		index++;
	}
	return -1;
}
