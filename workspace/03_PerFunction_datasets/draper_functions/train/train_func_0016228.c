X509_OBJECT_retrieve_match(STACK_OF(X509_OBJECT) *h, X509_OBJECT *x)
	{
	int idx, i;
	X509_OBJECT *obj;
	idx = sk_X509_OBJECT_find(h, x);
	if (idx == -1) return NULL;
	if ((x->type != X509_LU_X509) && (x->type != X509_LU_CRL))
		return sk_X509_OBJECT_value(h, idx);
	for (i = idx; i < sk_X509_OBJECT_num(h); i++)
		{
		obj = sk_X509_OBJECT_value(h, i);
		if (x509_object_cmp((const X509_OBJECT **)&obj, (const X509_OBJECT **)&x))
			return NULL;
		if (x->type == X509_LU_X509)
			{
			if (!X509_cmp(obj->data.x509, x->data.x509))
				return obj;
			}
		else if (x->type == X509_LU_CRL)
			{
			if (!X509_CRL_match(obj->data.crl, x->data.crl))
				return obj;
			}
		else
			return obj;
		}
	return NULL;
	}
