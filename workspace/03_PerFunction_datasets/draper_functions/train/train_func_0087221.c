read_headers(FILE *fp)
{
	struct rfc2045 *rfc2045p=rfc2045_alloc();
	static const char mv[]="Mime-Version: 1.0\n";
	char buf[BUFSIZ];
	char *s;
	const char *content_type, *content_transfer_encoding, *charset;

	rfc2045_parse(rfc2045p, mv, sizeof(mv)-1);

	while ((s=fgets(buf, sizeof(buf), fp)) != NULL)
	{
		rfc2045_parse(rfc2045p, s, strlen(s));
		if (strcmp(s, "\n") == 0 || strcmp(s, "\r\n") == 0)
			break;
	}
	rfc2045_parse_partial(rfc2045p);

	rfc2045_mimeinfo(rfc2045p, &content_type,
			 &content_transfer_encoding,
			 &charset);

	if (strcmp(content_type, "text/plain") ||
	    !rfc2045_isflowed(rfc2045p))
	{
		printf(getarg("ATT"), content_type);
		rfc2045_free(rfc2045p);
		return (-1);
	}

	rfc2045_free(rfc2045p);
	return (0);
}
