BIO_gets(BIO *b, char *in, int inl)
	{
	int i;
	long (*cb)(BIO *,int,const char *,int,long,long);

	if ((b == NULL) || (b->method == NULL) || (b->method->bgets == NULL))
		{
		BIOerr(BIO_F_BIO_GETS,BIO_R_UNSUPPORTED_METHOD);
		return(-2);
		}

	cb=b->callback;

	if ((cb != NULL) &&
		((i=(int)cb(b,BIO_CB_GETS,in,inl,0L,1L)) <= 0))
			return(i);

	if (!b->init)
		{
		BIOerr(BIO_F_BIO_GETS,BIO_R_UNINITIALIZED);
		return(-2);
		}

	i=b->method->bgets(b,in,inl);

	if (cb != NULL)
		i=(int)cb(b,BIO_CB_GETS|BIO_CB_RETURN,in,inl,
			0L,(long)i);
	return(i);
	}
