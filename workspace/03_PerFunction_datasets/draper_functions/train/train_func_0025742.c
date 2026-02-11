rfc1035_spf_gettxt_res(const char *current_domain,
			    char *buf,
			    struct rfc1035_res *res)
{
	struct	rfc1035_reply *reply;
	char	namebuf[RFC1035_MAXNAMESIZE+1];
	int n, o;


	namebuf[0]=0;
	strncat(namebuf, current_domain, RFC1035_MAXNAMESIZE);

	if (rfc1035_resolve_cname(res, namebuf,
				  RFC1035_TYPE_TXT, RFC1035_CLASS_IN,
				  &reply, 0) < 0 ||
	    reply == 0 ||
	    (n=rfc1035_replysearch_an(res, reply, namebuf, RFC1035_TYPE_TXT,
				      RFC1035_CLASS_IN, 0)) < 0)
	{
		switch (reply ? reply->rcode:
			RFC1035_RCODE_SERVFAIL) {
		case RFC1035_RCODE_NOERROR:
			rfc1035_replyfree(reply);
			return SPF_NONE;
		case RFC1035_RCODE_NXDOMAIN:
			rfc1035_replyfree(reply);
			return SPF_UNKNOWN;
		default:
			break;
		}
		if (reply)
			rfc1035_replyfree(reply);
		return SPF_ERROR;
	}

	while (n >= 0)
	{
		if (isspf1(reply, n))
			break;

		n=rfc1035_replysearch_an(res, reply, namebuf,
					 RFC1035_TYPE_TXT, RFC1035_CLASS_IN,
					 n+1);
	}

	if (n >= 0)
	{
		for (o=n; (o=rfc1035_replysearch_an(res, reply, namebuf,
						    RFC1035_TYPE_TXT,
						    RFC1035_CLASS_IN,
						    o+1)) >= 0; )
		{


			if (isspf1(reply, o))
			{
				rfc1035_replyfree(reply);
				return SPF_UNKNOWN;
			}
		}

		rfc1035_rr_gettxt(reply->allrrs[n], 0, buf);
		rfc1035_replyfree(reply);
		return SPF_PASS;
	}
	rfc1035_replyfree(reply);
	return SPF_UNKNOWN;
}
