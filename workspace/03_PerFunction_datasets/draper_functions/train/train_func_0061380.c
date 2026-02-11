trie_node_dump(trie_node_t * n, unsigned int depth) {
	int j;
	item_t * i;
	trie_node_t * node;

	if ( ! n ) {
		return;
	}

	i = n->children.head;
	for (j = 0; j <= depth; j++)
		fprintf(stderr, "  ");

	fprintf(stderr, "%s\n", n->key);

	while(i) {
		node = list_entry(i, trie_node_t, item);
		trie_node_dump(node, depth+1);
		i = i->next;
	}
}
