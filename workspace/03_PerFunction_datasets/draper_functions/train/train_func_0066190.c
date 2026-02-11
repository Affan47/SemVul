hash_get(struct hash *h, void *k)
{
	unsigned int bucket_index;

	bucket_index = h->hash(k) % h->size;
	if (list_empty(&h->buckets[bucket_index]))
		return NULL;

	list_foreach(struct hash_elem, e, &h->buckets[bucket_index], l)
		if (!h->cmp(e->data, k)) {
			return e->data;
		}
	end_list_foreach

	return NULL;
}
