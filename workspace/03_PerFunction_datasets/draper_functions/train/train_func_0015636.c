zFreeList(zList* l){
	l->current = l->head->next;
	while(l->current != l->tail){
		l->current = l->current->next;
		l->free_func(l->current->prev->data);
		zFree(l->current->prev);
	}
	zFree(l->head);
	zFree(l->tail);
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	l->current = l->dead->next;
	if(l->current != NULL){
		while(l->current->next != NULL){
			l->current = l->current->next;
			l->free_func(l->current->prev->data);
			zFree(l->current->prev);
		}
		l->free_func(l->current->data);
		zFree(l->current);
	}
	zFree(l->dead);
	l->dead = NULL;
	l->current = NULL;
}
