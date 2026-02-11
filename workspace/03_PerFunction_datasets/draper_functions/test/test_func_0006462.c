git_revpool_table_lookup(git_revpool_table *table, const git_oid *id)
{
	git_revpool_node *node;
	unsigned int index, hash;

	if (table == NULL)
		return NULL;

	hash = git_revpool_table__hash(id);
	index = (hash & table->size_mask);
	node = table->nodes[index];

	while (node != NULL) {
		if (node->hash == hash && git_oid_cmp(id, &node->object->id) == 0)
			return node->object;

		node = node->next;
	}

	return NULL;
}
