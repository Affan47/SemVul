slist_clear(slist* l)
{
	snode* nextnode;
	register snode* current;

	current = l->head;
	while (current) {
		nextnode=current->next;
		free(current->str);
		free(current->key);
		free(current);
		current=nextnode;
	}
	l->head = NULL;
	l->cur = NULL;
	l->cnt = 0;
}
