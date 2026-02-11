hashtable_create(int hashsize, int limit,
		 uint32_t (*hash)(const void *data,
		 		  const struct hashtable *table),
		 int (*compare)(const void *data1, const void *data2))
{
	int i;
	struct hashtable *h;
	int size = sizeof(struct hashtable)
		   + hashsize * sizeof(struct list_head);

	h = (struct hashtable *) calloc(size, 1);
	if (h == NULL) {
		errno = ENOMEM;
		return NULL;
	}

	for (i=0; i<hashsize; i++)
		INIT_LIST_HEAD(&h->members[i]);

	h->hashsize = hashsize;
	h->limit = limit;
	h->hash = hash;
	h->compare = compare;

	return h;
}
