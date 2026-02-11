git_hashtable_lookup(git_hashtable *self, const void *key)
{
	int hash_id;
	git_hashtable_node *node;

	assert(self && self->nodes);

	for (hash_id = 0; hash_id < GIT_HASHTABLE_HASHES; ++hash_id) {
		node = node_with_hash(self, key, hash_id);
		if (node->key && self->key_equal(key, node->key) == 0)
			return node->value;
	}

	return NULL;
}
