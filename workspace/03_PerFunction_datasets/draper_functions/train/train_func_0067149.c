find_entry_for_token (char *token)
{
	int i;

	for (i = 0; i < nb_entries; i++) {
		HashEntry *e = &(entries[i]);
		if (!strcmp (e->key, token))
			return e;
	}
	return NULL;
}
