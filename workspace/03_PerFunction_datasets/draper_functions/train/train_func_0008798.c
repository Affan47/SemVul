EC_KEY_insert_key_method_data(EC_KEY *key, void *data,
	void *(*dup_func)(void *), void (*free_func)(void *), void (*clear_free_func)(void *))
	{
	EC_EXTRA_DATA *ex_data;

	CRYPTO_w_lock(CRYPTO_LOCK_EC);
	ex_data = EC_EX_DATA_get_data(key->method_data, dup_func, free_func, clear_free_func);
	if (ex_data == NULL)
		EC_EX_DATA_set_data(&key->method_data, data, dup_func, free_func, clear_free_func);
	CRYPTO_w_unlock(CRYPTO_LOCK_EC);

	return ex_data;
	}
