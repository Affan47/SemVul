_wi_set_copy(wi_runtime_instance_t *instance) {
	wi_set_t			*set = instance, *set_copy;
	_wi_set_bucket_t	*bucket;
	wi_uinteger_t		i, j;

	set_copy = wi_set_init_with_capacity_and_callbacks(wi_set_alloc(), set->data_count, set->counted, set->callbacks);

	for(i = 0; i < set->buckets_count; i++) {
		for(bucket = set->buckets[i]; bucket; bucket = bucket->next) {
			for(j = 0; j < bucket->count; j++)
				_wi_set_add_data(set_copy, bucket->data);
		}
	}

	return set_copy;
}
