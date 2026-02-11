dsa_copy_parameters(EVP_PKEY *to, const EVP_PKEY *from)
	{
	BIGNUM *a;

	if ((a=BN_dup(from->pkey.dsa->p)) == NULL)
		return 0;
	if (to->pkey.dsa->p != NULL)
		BN_free(to->pkey.dsa->p);
	to->pkey.dsa->p=a;

	if ((a=BN_dup(from->pkey.dsa->q)) == NULL)
		return 0;
	if (to->pkey.dsa->q != NULL)
		BN_free(to->pkey.dsa->q);
	to->pkey.dsa->q=a;

	if ((a=BN_dup(from->pkey.dsa->g)) == NULL)
		return 0;
	if (to->pkey.dsa->g != NULL)
		BN_free(to->pkey.dsa->g);
	to->pkey.dsa->g=a;
	return 1;
	}
