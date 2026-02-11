itable_double_buckets(struct itable *h)
{
	struct itable *hn = itable_create(2 * h->bucket_count);

	if(!hn)
		return 0;


	uint64_t key;
	void *value;
	itable_firstkey(h);
	while(itable_nextkey(h, &key, &value))
		if(!itable_insert(hn, key, value))
		{
			itable_delete(hn);
			return 0;
		}


	struct entry *e, *f;
	int i;
	for(i = 0; i < h->bucket_count; i++) {
		e = h->buckets[i];
		while(e) {
			f = e->next;
			free(e);
			e = f;
		}
	}


	free(h->buckets);
	h->buckets      = hn->buckets;
	h->bucket_count = hn->bucket_count;
	h->size         = hn->size;


	free(hn);

	return 1;
}
