mono_mempool_strdup (MonoMemPool *pool,
					 const char *s)
{
	int l;
	char *res;

	if (s == NULL)
		return NULL;

	l = strlen (s);
	res = mono_mempool_alloc (pool, l + 1);
	memcpy (res, s, l + 1);

	return res;
}
