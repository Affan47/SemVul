TXT_DB_write(BIO *out, TXT_DB *db)
	{
	long i,j,n,nn,l,tot=0;
	char *p,**pp,*f;
	BUF_MEM *buf=NULL;
	long ret= -1;

	if ((buf=BUF_MEM_new()) == NULL)
		goto err;
	n=sk_OPENSSL_PSTRING_num(db->data);
	nn=db->num_fields;
	for (i=0; i<n; i++)
		{
		pp=sk_OPENSSL_PSTRING_value(db->data,i);

		l=0;
		for (j=0; j<nn; j++)
			{
			if (pp[j] != NULL)
				l+=strlen(pp[j]);
			}
		if (!BUF_MEM_grow_clean(buf,(int)(l*2+nn))) goto err;

		p=buf->data;
		for (j=0; j<nn; j++)
			{
			f=pp[j];
			if (f != NULL)
				for (;;)
					{
					if (*f == '\0') break;
					if (*f == '\t') *(p++)='\\';
					*(p++)= *(f++);
					}
			*(p++)='\t';
			}
		p[-1]='\n';
		j=p-buf->data;
		if (BIO_write(out,buf->data,(int)j) != j)
			goto err;
		tot+=j;
		}
	ret=tot;
err:
	if (buf != NULL) BUF_MEM_free(buf);
	return(ret);
	}
