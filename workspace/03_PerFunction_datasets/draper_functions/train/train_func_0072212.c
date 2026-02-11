X509_LOOKUP_new(X509_LOOKUP_METHOD *method)
	{
	X509_LOOKUP *ret;

	ret=(X509_LOOKUP *)OPENSSL_malloc(sizeof(X509_LOOKUP));
	if (ret == NULL) return NULL;

	ret->init=0;
	ret->skip=0;
	ret->method=method;
	ret->method_data=NULL;
	ret->store_ctx=NULL;
	if ((method->new_item != NULL) && !method->new_item(ret))
		{
		OPENSSL_free(ret);
		return NULL;
		}
	return ret;
	}
