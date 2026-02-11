hash_free(struct hash *h, void (*free_fn)(void *))
{
	unsigned int i;

	for (i = 0; i < h->size; i++) {
		list_foreach_safe(struct hash_elem, e, &h->buckets[i], l)
			if (free_fn)
				free_fn(e->data);
			free(e);
		end_list_foreach
	}

	free(h);
}
