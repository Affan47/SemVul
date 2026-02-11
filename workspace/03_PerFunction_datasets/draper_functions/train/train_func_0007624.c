nc_uri(ASN1_IA5STRING *uri, ASN1_IA5STRING *base)
	{
	const char *baseptr = (char *)base->data;
	const char *hostptr = (char *)uri->data;
	const char *p = strchr(hostptr, ':');
	int hostlen;

	if (!p || (p[1] != '/') || (p[2] != '/'))
		return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;
	hostptr = p + 3;


	p = strchr(hostptr, ':');

	if (!p)
		p = strchr(hostptr, '/');

	if (!p)
		hostlen = strlen(hostptr);
	else
		hostlen = p - hostptr;

	if (hostlen == 0)
		return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;


	if (*baseptr == '.')
		{
		if (hostlen > base->length)
			{
			p = hostptr + hostlen - base->length;
			if (!strncasecmp(p, baseptr, base->length))
				return X509_V_OK;
			}
		return X509_V_ERR_PERMITTED_VIOLATION;
		}

	if ((base->length != (int)hostlen) || strncasecmp(hostptr, baseptr, hostlen))
		return X509_V_ERR_PERMITTED_VIOLATION;

	return X509_V_OK;

	}
