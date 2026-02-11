speciallist_destroy (speciallist_t *list){
	speciallist_node_t *last = list->first;
	speciallist_node_t *next;

	speciallist_lock(list);
	while (last){
		next = last->next;
		free(last);
		last = next;
	}
	speciallist_unlock(list);

	free(list);
	list = NULL;
}
