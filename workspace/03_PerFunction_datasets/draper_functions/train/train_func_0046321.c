hash_table_iterate(HashTable *hash_table, HashTableIterator *iterator)
{
	unsigned int chain;

	iterator->hash_table = hash_table;


	iterator->next_entry = NULL;


	for (chain=0; chain<hash_table->table_size; ++chain) {

		if (hash_table->table[chain] != NULL) {
			iterator->next_entry = hash_table->table[chain];
			iterator->next_chain = chain;
			break;
		}
	}
}
