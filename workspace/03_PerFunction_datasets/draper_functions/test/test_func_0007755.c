_wi_dictionary_dealloc(wi_runtime_instance_t *instance) {
	wi_dictionary_t				*dictionary = instance;
	_wi_dictionary_bucket_t		*bucket;
	wi_uinteger_t				i;

	for(i = 0; i < dictionary->buckets_count; i++) {
		for(bucket = dictionary->buckets[i]; bucket; bucket = bucket->next) {
			_WI_DICTIONARY_VALUE_RELEASE(dictionary, bucket->data);
			_WI_DICTIONARY_KEY_RELEASE(dictionary, bucket->key);
		}
	}

	if(dictionary->bucket_chunks) {
		for(i = 0; i < dictionary->bucket_chunks_count; i++)
			wi_free(dictionary->bucket_chunks[i]);

		wi_free(dictionary->bucket_chunks);
	}

	wi_free(dictionary->buckets);

	wi_release(dictionary->lock);
}
