git_hashtable_remove(git_hashtable *table, const void *key)
{
	git_hashtable_node *node, *prev_node;
	uint32_t index, hash;

	assert(table);

	hash = table->hash(key);
	index = (hash & table->size_mask);
	node = table->nodes[index];

	prev_node = NULL;

	while (node != NULL) {
		if (node->hash == hash && table->key_equal(node->object, key)) {
			if (prev_node == NULL)
				table->nodes[index] = node->next;
			else
				prev_node->next = node->next;

			free(node);
			return GIT_SUCCESS;
		}

		prev_node = node;
		node = node->next;
	}

	return GIT_ENOTFOUND;
}
