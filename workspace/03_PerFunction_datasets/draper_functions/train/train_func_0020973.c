list_msg_textplain(struct rfc2045 *rfc, FILE *fp)
{
	const char *mime_charset, *dummy;
	int rc;
	struct rfc2045src *src;

        rfc2045_mimeinfo(rfc, &dummy, &dummy, &mime_charset);

        if (strcasecmp(mime_charset, charset))
        {
		printf(gettext("    (The following text was converted from %s)\n\n"),
		       mime_charset);
	}

	src=rfc2045src_init_fd(fileno(fp));

	if (src == NULL)
		return (-1);

	rc=rfc2045_decodetextmimesection(src,
					 rfc,
					 charset,
					 NULL,
					 textplain_output, NULL);

	printf("\n");
	rfc2045src_deinit(src);
	return (rc);
}
