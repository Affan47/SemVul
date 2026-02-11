setexp(const char *exp,
		   struct rfc1035_spf_info *info)
{
	struct	rfc1035_reply *reply;
	char	namebuf[RFC1035_MAXNAMESIZE+1];
	char	txtbuf[256];
	int n;
	char	*str;


	namebuf[0]=0;
	strncat(namebuf, exp, RFC1035_MAXNAMESIZE);

	if (rfc1035_resolve_cname(&rfc1035_default_resolver,
				  RFC1035_RESOLVE_RECURSIVE, namebuf,
				  RFC1035_TYPE_TXT, RFC1035_CLASS_IN,
				  &reply, 0) < 0 ||
	    reply == 0 ||
	    (n=rfc1035_replysearch_an(&rfc1035_default_resolver,
				      reply, namebuf, RFC1035_TYPE_TXT,
				      RFC1035_CLASS_IN, 0)) < 0)
	{
		set_err_msg(info->errmsg_buf,
			    info->errmsg_buf_size,
			    "A DNS lookup error occured while"
			    " fetching the SPF explanation record.");
	}
	else
	{
		rfc1035_rr_gettxt(reply->allrrs[n], 0, txtbuf);

		str=expand(txtbuf, info);

		set_err_msg(info->errmsg_buf,
			    info->errmsg_buf_size,
			    str ? str:strerror(errno));
		if (str)
			free(str);
	}
	rfc1035_replyfree(reply);
}
