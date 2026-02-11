hm_hash_remove(hm_hash_t *table, const char *key){
	if (key == NULL)
		return 0;

	hm_capacity_t index = _hm_hash_getbucketforkey(table, key);

	if (index == 0)
		return 0;

	hm_collision_list_t *bucket = & table->buckets[index - 1];

	table->datacount -= hm_vector_count(bucket);
	table->datasize  -= hm_vector_sizeof(bucket);
	int result = hm_vector_remove(bucket, key);
	table->datasize  += hm_vector_sizeof(bucket);
	table->datacount += hm_vector_count(bucket);

	return result;
}
