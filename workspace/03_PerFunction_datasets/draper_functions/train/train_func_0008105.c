COMP_CTX_new(COMP_METHOD *meth)
	{
	COMP_CTX *ret;

	if ((ret=(COMP_CTX *)OPENSSL_malloc(sizeof(COMP_CTX))) == NULL)
		{

		return(NULL);
		}
	memset(ret,0,sizeof(COMP_CTX));
	ret->meth=meth;
	if ((ret->meth->init != NULL) && !ret->meth->init(ret))
		{
		OPENSSL_free(ret);
		ret=NULL;
		}
	return(ret);
	}
