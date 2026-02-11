verifypeer(const struct tls_info *info, SSL *ssl)
{
	X509 *x=NULL;
	X509_NAME *subj=NULL;
	int nentries, j;
	char domain[256];
	char *p;
	char errmsg[1000];

	if (!info->peer_verify_domain)
		return (1);

	if (info->isserver)
	{
		x=SSL_get_peer_certificate(ssl);

		if (x)
			subj=X509_get_subject_name(x);
	}
	else
	{
		STACK_OF(X509) *peer_cert_chain=SSL_get_peer_cert_chain(ssl);

		if (peer_cert_chain && peer_cert_chain->stack.num > 0)
		{
			X509 *xx=(X509 *)peer_cert_chain->stack.data[0];

			if (xx)
				subj=X509_get_subject_name(xx);
		}
	}


	nentries=0;
	if (subj)
		nentries=X509_NAME_entry_count(subj);

	domain[0]=0;
	for (j=0; j<nentries; j++)
	{
		const char *obj_name;
		X509_NAME_ENTRY *e;
		ASN1_OBJECT *o;
		ASN1_STRING *d;

		int dlen;
		unsigned char *ddata;

		e=X509_NAME_get_entry(subj, j);
		if (!e)
			continue;

		o=X509_NAME_ENTRY_get_object(e);
		d=X509_NAME_ENTRY_get_data(e);

		if (!o || !d)
			continue;

		obj_name=OBJ_nid2sn(OBJ_obj2nid(o));

		dlen=ASN1_STRING_length(d);
		ddata=ASN1_STRING_data(d);

		if (strcasecmp(obj_name, "CN") == 0)
		{
			if (dlen >= sizeof(domain)-1)
				dlen=sizeof(domain)-1;

			memcpy(domain, ddata, dlen);
			domain[dlen]=0;
		}
	}

	if (x)
		X509_free(x);
	p=domain;

	if (*p == '*')
	{
		int	pl, l;

		pl=strlen(++p);
		l=strlen(info->peer_verify_domain);

		if (*p == '.' && pl <= l &&
		    strcasecmp(info->peer_verify_domain+l-pl, p) == 0)
			return (1);
	}
	else if (strcasecmp(info->peer_verify_domain, p) == 0)
		return (1);

	strcpy(errmsg, "couriertls: Mismatched SSL certificate: CN=");
	strcat(errmsg, domain);
	strcat(errmsg, " (expected ");
	strncat(errmsg, info->peer_verify_domain, 256);
	strcat(errmsg, ")");
	(*info->tls_err_msg)(errmsg, info->app_data);
	return (0);
}
