X509_set_notBefore(X509 *x, const ASN1_TIME *tm)
	{
	ASN1_TIME *in;

	if ((x == NULL) || (x->cert_info->validity == NULL)) return(0);
	in=x->cert_info->validity->notBefore;
	if (in != tm)
		{
		in=M_ASN1_TIME_dup(tm);
		if (in != NULL)
			{
			M_ASN1_TIME_free(x->cert_info->validity->notBefore);
			x->cert_info->validity->notBefore=in;
			}
		}
	return(in != NULL);
	}
