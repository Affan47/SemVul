htable_put(t_htable *htable, t_htable_node *node)
{
	t_htable_node **head;

	node->hash = htable->hash(node);
	head = &htable->table[node->hash % htable->table_size];
	node->prev = NULL;
	node->next = *head;
	while (node->next != NULL && htable->compare(node->next, node) < 0) {
		node->prev = node->next;
		node->next = node->next->next;
	}
	if (node->prev == NULL) {
		*head = node;
	} else {
		node->prev->next = node;
	}
	if (node->next != NULL) {
		node->next->prev = node;
	}
	htable->size++;
}
