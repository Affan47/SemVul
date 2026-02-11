set_iterate(Set *set, SetIterator *iter)
{
	unsigned int chain;

	iter->set = set;
	iter->next_entry = NULL;


	for (chain = 0; chain < set->table_size; ++chain) {


		if (set->table[chain] != NULL) {
			iter->next_entry = set->table[chain];
			break;
		}
	}

	iter->next_chain = chain;
}
