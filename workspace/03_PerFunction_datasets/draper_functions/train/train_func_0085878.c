fr_hash_table_insert(fr_hash_table_t *ht, void *data)
{
	uint32_t key;
	uint32_t entry;
	uint32_t reversed;
	fr_hash_entry_t *node;

	if (!ht || !data) return 0;

	key = ht->hash(data);
	entry = key & ht->mask;
	reversed = reverse(key);

	if (!ht->buckets[entry]) fr_hash_table_fixup(ht, entry);


	node = malloc(sizeof(*node));
	if (!node) return 0;
	memset(node, 0, sizeof(*node));

	node->next = &ht->null;
	node->reversed = reversed;
	node->key = key;
	node->data = data;


	if (!list_insert(ht, &ht->buckets[entry], node)) {
		free(node);
		return 0;
	}


	ht->num_elements++;
	if (ht->num_elements >= ht->next_grow) {
		fr_hash_table_grow(ht);
	}

	return 1;
}
