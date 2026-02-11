git_hashtable_lookup(git_hashtable *table, const void *key)
{
	git_hashtable_node *node;
	uint32_t index, hash;

	assert(table);

	hash = table->hash(key);
	index = (hash & table->size_mask);
	node = table->nodes[index];

	while (node != NULL) {
		if (node->hash == hash && table->key_equal(node->object, key))
			return node->object;

		node = node->next;
	}

	return NULL;
}
