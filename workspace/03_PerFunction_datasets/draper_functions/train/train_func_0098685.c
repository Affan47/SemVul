trie_delete2(trie_t * t, trie_node_t * node) {
	item_t * i;
	trie_node_t * n;

	assert(t);
	if ( list_length(&node->children) == 0 ) {
		if (node != t->root) {
			list_remove2(&node->item);
			t->delete_node(node);
			node = NULL;
		}
		return TRIE_OK;
	} else {
		i = node->children.head;

		while (i) {
			n = list_entry(i, trie_node_t, item);
			i = i->next;
			trie_delete2(t, n);
		}

		if (node != t->root) {
			list_remove2(&node->item);
			t->delete_node(node);
			node = NULL;
		}
		return TRIE_MANY;
	}
}
