get_pw_nam(char * name, struct hashtable* ht,
				    struct mypasswd **last_found)
{
	int h;
	struct mypasswd * hashentry;

	if (!ht || !name || *name == '\0') return NULL;
	*last_found = NULL;
	if (ht->tablesize > 0) {
		h = hash (name, ht->tablesize);
		for (hashentry = ht->table[h]; hashentry; hashentry = hashentry->next)
			if (!strcmp(hashentry->field[ht->keyfield], name)){

				*last_found=hashentry->next;
				return hashentry;
			}
		return NULL;
	}
	if (ht->fp) {
		fclose(ht->fp);
		ht->fp = NULL;
	}
	if (!(ht->fp=fopen(ht->filename, "r"))) return NULL;
	return get_next(name, ht, last_found);
}
