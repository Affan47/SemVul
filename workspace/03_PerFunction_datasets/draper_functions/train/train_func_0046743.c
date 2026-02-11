md_free(BIO *a)
	{
	if (a == NULL) return(0);
	EVP_MD_CTX_destroy(a->ptr);
	a->ptr=NULL;
	a->init=0;
	a->flags=0;
	return(1);
	}
