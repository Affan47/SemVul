mget(ArrayString& akeys) {
	VHash &hresult = *new VHash();

	size_t kl = akeys.count();

	if(kl==0)
		return hresult;

	const char **keys = new const char *[kl];
	size_t *key_lengths = new size_t[kl];

	for(size_t i=0; i<kl; i++){
		const String &skey = *(akeys[i]);
		check_key(skey);
		keys[i] = skey.cstr();
		key_lengths[i] = skey.length();
	}

	check("mget", fm, f_memcached_mget(fm, keys, key_lengths, kl));


	memcached_result_st *results=0;
	memcached_return rc;

	while((results=f_memcached_fetch_result(fm, results, &rc)) && (rc == MEMCACHED_SUCCESS)){
		const char *hkey = pa_strdup(f_memcached_result_key_value(results), f_memcached_result_key_length(results));
		Serialization_data data(f_memcached_result_flags(results), f_memcached_result_value(results), f_memcached_result_length(results));

		hresult.hash().put(hkey, &deserialize(data));
	}

	if (rc != MEMCACHED_END && rc != MEMCACHED_NOTFOUND)
		error("mget", fm, rc);

	delete keys;
	delete key_lengths;

	return hresult;
}
