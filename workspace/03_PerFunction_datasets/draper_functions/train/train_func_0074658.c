linkdb_erase( struct linkdb_node** head, void *key)
{
	struct linkdb_node *node;

	if( head == NULL ) return NULL;
	node = *head;
	while( node ) {
		if( node->key == key ) {
			void *old_data = node->data;
			if( node->prev == NULL )
				*head = node->next;
			else
				node->prev->next = node->next;
			if( node->next )
				node->next->prev = node->prev;
			aFree( node );
			return old_data;
		}
		node = node->next;
	}
	return NULL;
}
