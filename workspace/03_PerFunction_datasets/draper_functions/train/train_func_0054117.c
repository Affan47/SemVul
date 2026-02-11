memusage_sort_frames(const memusage_t *mu, bool periodic,
	hash_table_t *ht, struct callframe_filler *fill)
{
	size_t count;

	memusage_check(mu);
	g_assert(ht != NULL);

	fill->mu = mu;
	fill->periodic = periodic;


	count = hash_table_size(ht);
	XMALLOC_ARRAY(fill->array, count);
	while (hash_table_size(ht) != count) {
		count = hash_table_size(ht);
		XREALLOC_ARRAY(fill->array, count);
	}
	fill->capacity = count;
	fill->count = 0;

	hash_table_foreach(ht, callframe_filler_add, fill);

	g_assert(fill->count == fill->capacity);

	vsort(fill->array, fill->count, sizeof fill->array[0], callframe_cmp);
}
