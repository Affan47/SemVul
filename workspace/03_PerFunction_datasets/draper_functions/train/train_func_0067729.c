int_thread_release(LHASH_OF(ERR_STATE) **hash)
	{
	int i;

	if (hash == NULL || *hash == NULL)
		return;

	i = CRYPTO_add(&int_thread_hash_references, -1, CRYPTO_LOCK_ERR);

#ifdef REF_PRINT
	fprintf(stderr,"%4d:%s\n",int_thread_hash_references,"ERR");
#endif
	if (i > 0) return;
#ifdef REF_CHECK
	if (i < 0)
		{
		fprintf(stderr,"int_thread_release, bad reference count\n");
		abort();
		}
#endif
	*hash = NULL;
	}
