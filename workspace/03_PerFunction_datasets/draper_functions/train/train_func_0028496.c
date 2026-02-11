dh_pub_cmp(const EVP_PKEY *a, const EVP_PKEY *b)
	{
	if (dh_cmp_parameters(a, b) == 0)
		return 0;
	if (BN_cmp(b->pkey.dh->pub_key,a->pkey.dh->pub_key) != 0)
		return 0;
	else
		return 1;
	}
