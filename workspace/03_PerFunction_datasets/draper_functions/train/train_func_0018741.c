cred_encoding_create()
{
	private_cred_encoding_t *this;
	cred_encoding_type_t type;

	INIT(this,
		.public = {
			.encode = (bool(*)(cred_encoding_t*, cred_encoding_type_t type, void *cache, chunk_t *encoding, ...))encode,
			.get_cache = _get_cache,
			.cache = _cache,
			.clear_cache = _clear_cache,
			.add_encoder = _add_encoder,
			.remove_encoder = _remove_encoder,
			.destroy = _destroy,
		},
		.encoders = linked_list_create(),
		.lock = rwlock_create(RWLOCK_TYPE_DEFAULT),
	);

	for (type = 0; type < CRED_ENCODING_MAX; type++)
	{
		this->cache[type] = hashtable_create(hashtable_hash_ptr,
											 hashtable_equals_ptr, 8);
	}

	return &this->public;
}
