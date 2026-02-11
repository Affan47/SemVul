rfc2045_decodemsgtoutf8(struct rfc2045src *src,
			    struct rfc2045 *p,
			    struct rfc2045_decodemsgtoutf8_cb *callback)
{
	struct rfc2045headerinfo *hi;
	int rc;

	hi=rfc2045header_start(src, p);

	if (hi)
	{
		char *header;
		char *value;

		while (rfc2045header_get(hi, &header, &value,
					 RFC2045H_NOLC |
					 RFC2045H_KEEPNL) == 0 && header)
		{
			if (callback->flags & RFC2045_DECODEMSG_NOHEADERS)
				continue;

			if (doconvtoutf8_rfc822hdr(header, value,
						   callback) < 0)
				return -1;
		}
		rfc2045header_end(hi);
	}

	if (p->firstpart)
	{
		for (p=p->firstpart; p; p=p->next)
		{
			if (!p->isdummy)
			{
				if ((rc=rfc2045_decodemsgtoutf8(src, p,
								callback))
				    != 0)
					return rc;
			}
		}
	}
	else
	{
		const char *content_type;
		const char *transfer_encoding;
		const char *charset;
		struct doconvtoutf8_info info;

		info.callback=callback;

		rfc2045_mimeinfo(p, &content_type, &transfer_encoding,
				 &charset);

		if (strncmp(content_type, "text/", 5) == 0 &&
		    (callback->flags & RFC2045_DECODEMSG_NOBODY) == 0 &&
		    (rc=rfc2045_decodetextmimesection(src, p, "utf-8", NULL,
						      decode_handler,
						      &info)) != 0)
			return rc;
	}
	return 0;
}
