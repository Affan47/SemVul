EVP_PKEY_cmp(const EVP_PKEY *a, const EVP_PKEY *b)
	{
	if (a->type != b->type)
		return -1;

	if (a->ameth)
		{
		int ret;

		if (a->ameth->param_cmp)
			{
			ret = a->ameth->param_cmp(a, b);
			if (ret <= 0)
				return ret;
			}

		if (a->ameth->pub_cmp)
			return a->ameth->pub_cmp(a, b);
		}

	return -2;
	}
