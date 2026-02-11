alg_filter(uintptr_t type, entry_t **in, u_int16_t *alg,
					   void **unused, u_int16_t *key_size)
{
	entry_t *entry = *in;

	if (entry->type != type)
	{
		return FALSE;
	}
	if (alg)
	{
		*alg = entry->alg;
	}
	if (key_size)
	{
		*key_size = entry->key_size;
	}
	return TRUE;
}
