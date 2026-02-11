patricia_put(patricia_t* trie, const void* key, const void* value) {

	patricia_node_t* nearest = node_search(trie->root->left, key, -1);

	if(key_eq(key, nearest->key)) {
		nearest->key = key;
		nearest->value = value;
	}
	else {
		int32_t msd = 0;
		while(key_isset(key, msd)==key_isset(nearest->key, msd)) msd++;

		patricia_node_t* new_node = node_alloc(trie, key, value, msd);
		trie->root->left = node_put(new_node, trie->root->left, trie->root);
	}
}
