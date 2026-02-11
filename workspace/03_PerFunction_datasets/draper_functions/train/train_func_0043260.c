fch_buckets_get_indexes_sorted_by_size(fch_buckets_t * buckets)
{
	cmph_uint32 i = 0;
	cmph_uint32 sum = 0, value;
	cmph_uint32 *nbuckets_size = (cmph_uint32 *) calloc((size_t)buckets->max_size + 1, sizeof(cmph_uint32));
	cmph_uint32 * sorted_indexes = (cmph_uint32 *) calloc((size_t)buckets->nbuckets, sizeof(cmph_uint32));


	for(i = 0; i < buckets->nbuckets; i++) nbuckets_size[fch_bucket_size(buckets->values + i)] ++;


	value = nbuckets_size[buckets->max_size];
	nbuckets_size[buckets->max_size] = sum;
	for(i = (int)buckets->max_size - 1; i >= 0; i--)
	{
		sum += value;
		value = nbuckets_size[i];
		nbuckets_size[i] = sum;

	}
	for(i = 0; i < buckets->nbuckets; i++)
	{
		sorted_indexes[nbuckets_size[fch_bucket_size(buckets->values + i)]] = (cmph_uint32)i;
		nbuckets_size[fch_bucket_size(buckets->values + i)] ++;
	}
	free(nbuckets_size);
	return sorted_indexes;
}
