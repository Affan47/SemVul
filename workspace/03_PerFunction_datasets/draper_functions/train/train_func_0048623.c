EVP_PKEY_meth_get0_info(int *ppkey_id, int *pflags,
				const EVP_PKEY_METHOD *meth)
	{
	if (ppkey_id)
		*ppkey_id = meth->pkey_id;
	if (pflags)
		*pflags = meth->flags;
	}
