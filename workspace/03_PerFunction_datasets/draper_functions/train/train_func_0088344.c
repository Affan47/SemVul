mime_filter_html_run (CamelMimeFilter *mime_filter,
                      const gchar *in,
                      gsize inlen,
                      gsize prespace,
                      gchar **out,
                      gsize *outlenptr,
                      gsize *outprespace,
                      gint last)
{
	CamelMimeFilterHTMLPrivate *priv;
	camel_html_parser_t state;
	gchar *outp;

	priv = CAMEL_MIME_FILTER_HTML_GET_PRIVATE (mime_filter);

	d (printf ("converting html:\n%.*s\n", (gint) inlen, in));


	camel_mime_filter_set_size (mime_filter, inlen * 2 + 256, FALSE);
	outp = mime_filter->outbuf;

	camel_html_parser_set_data (priv->ctxt, in, inlen, last);
	do {
		const gchar *data;
		gint len;

		state = camel_html_parser_step (priv->ctxt, &data, &len);

		switch (state) {
		case CAMEL_HTML_PARSER_DATA:
		case CAMEL_HTML_PARSER_ENT:
			memcpy (outp, data, len);
			outp += len;
			break;
		case CAMEL_HTML_PARSER_ELEMENT:

			break;
		default:

			break;
		}
	} while (state != CAMEL_HTML_PARSER_EOF && state != CAMEL_HTML_PARSER_EOD);

	*out = mime_filter->outbuf;
	*outlenptr = outp - mime_filter->outbuf;
	*outprespace = mime_filter->outbuf - mime_filter->outreal;

	d (printf ("converted html end:\n%.*s\n", (gint) * outlenptr, *out));
}
